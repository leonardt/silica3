import silica as si
from silica import uint, eval, memory, bit, bits
import math
import fault
import magma as m
from bit_vector import BitVector


@si.combinational
def saturating_add(a : si.UInt(7), b : si.UInt(7), max_ : si.UInt(7)) -> si.UInt(7):
    c = a + b
    if c == max_:
        c = 0
    return c


@si.generator
def FillingState(lbmem_width, depth, lbmem, raddr, waddr):
    # Linebuffer filling state
    # rdata is always invalid
    # Remains in this state until `lbmem_width` writes have occured (wen is high for `lbmem` cycles)
    for i in range(lbmem_width):
        valid = bit(0)
        rdata = lbmem[raddr]
        wdata, wen = yield rdata, valid
        while ~wen:
            wdata, wen = yield rdata, valid
        lbmem[waddr] = wdata
        # waddr = saturating_add(waddr, bit(1), bits(depth, 7))
        waddr = waddr + 1
    return waddr

@si.generator
def DrainingState(lbmem_width, depth, lbmem, raddr, waddr):
    # Linebuffer draining state
    # rdata is always valid
    # Remains in this state until `lbmem_width` cycles without a write have occured
    not_drained = bits(lbmem_width - 1, 3)
    while not_drained:
        valid = bit(1)
        rdata = lbmem[raddr]
        wdata, wen = yield rdata, valid
        # raddr = saturating_add(raddr, bit(1), bits(depth, 7))
        raddr = raddr + 1
        if wen:
            lbmem[waddr] = wdata
            # waddr = saturating_add(waddr, bit(1), bits(depth, 7))
            waddr = waddr + 1
        else:
            not_drained = not_drained - bits(1, 3)
    valid = bit(1)
    rdata = lbmem[raddr]
    wdata, wen = yield rdata, valid
    raddr = raddr + 1
    return waddr, raddr

@si.coroutine(inputs={"wdata": si.Bits(8), "wen": si.Bit})
def LbMem(depth=64, lbmem_width=8):
    lbmem = memory(depth, lbmem_width)
    raddr = uint(0, eval(math.ceil(math.log2(depth))))
    waddr = uint(0, eval(math.ceil(math.log2(depth))))
    while True:
        waddr = yield from FillingState(lbmem_width, depth, lbmem, raddr, waddr)
        waddr, raddr = yield from DrainingState(lbmem_width, depth, lbmem, raddr, waddr)

@si.coroutine
def inputs_generator(inputs):
    while True:
        for wdata, wen in inputs:
            yield wdata, wen

def test_lbmem():
    lbmem = LbMem()
    # si_lbmem = si.compile(lbmem, "tests/build/si_lbmem.v")
    si_lbmem = m.DefineFromVerilogFile("verilog/lbmem.v", type_map={"CLK":
                                                                    m.In(m.Clock)})[0]
    tester = fault.Tester(si_lbmem, si_lbmem.CLK)
    # wdata = [BitVector(i, 16) for i in range(40)]
    # wen =   [BitVector(i%2) for i in range(40)]
    expected_written = []
    expected_valid = False
    num_writes = 0
    # for cycle, inputs in enumerate(zip(wdata,wen)):
    for i in range(0, 8):
        tester.poke(si_lbmem.wdata, i)
        tester.poke(si_lbmem.wen, 1)
        lbmem.send((i, BitVector(1)))
        tester.step(2)
        assert lbmem.valid == (i == 7)
        tester.print(si_lbmem.valid)
        tester.expect(si_lbmem.valid, i == 7), "Valid only on last write"
        assert lbmem.rdata == 0, "should be 0, even on first read"
        tester.expect(si_lbmem.rdata, 0)
    for i in range(0, 8):
        tester.poke(si_lbmem.wdata, 0)
        tester.poke(si_lbmem.wen, 0)
        lbmem.send((0, BitVector(0)))
        tester.step(2)
        # i + 1  because 0 was read on the final write, 7 when i == 7 because
        # there's nothing left to drain
        rdata = i + 1 if i != 7 else 0
        valid = i < 7
        assert lbmem.rdata == rdata, i
        assert lbmem.valid == valid, i
        tester.expect(si_lbmem.rdata, rdata)
        tester.print(si_lbmem.valid)
        tester.expect(si_lbmem.valid, valid)
    tester.eval()
        # print(f"inputs={inputs}, rdata={lbmem.rdata}, valid={lbmem.valid}")
        # wen = inputs[1]
        # if wen:
        #     expected_written.append(inputs[0])
        # num_writes += wen.as_int()
        # if not expected_valid and num_writes == 8:
        #     expected_valid = True
        #     drain_state = 8
        # if expected_valid and drain_state and not wen:
        #     drain_state -= 1
        # if expected_valid and not drain_state:
        #     expected_valid = False
        #     num_writes = 0
        # assert expected_valid == lbmem.valid
        # tester.expect(si_lbmem.valid, lbmem.valid)
        # if expected_valid:
        #     rdata = expected_written.pop(0)
        #     assert lbmem.rdata == rdata
        #     tester.expect(si_lbmem.rdata, rdata)
        # print(drain_state)

    tester.compile_and_run(target="verilator", directory="tests/build",
                           flags=['-Wno-fatal'])