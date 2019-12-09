import logging
logging.basicConfig(level=logging.DEBUG)
import random
import silica as si
from silica import bits
import fault
import magma as m


class Downsample(si.Process):
    inputs = {
        "data_in": si.Channel(16)
    }
    outputs = {
        "data_out": si.Channel(16)
    }

    def main(self):
        x = bits(0, 5)
        y = bits(0, 5)
        yield
        while True:
            y = 0
            while True:
                x = 0
                while True:
                    data = self.data_in.pop()
                    if ((x % bits(2, 5)) == 0) & ((y % bits(2, 5)) == 0):
                        self.data_out.push(data)
                    yield
                    if x == 31:
                        yield
                        break
                    x = x + 1
                if y == 31:
                    break
                y = y + 1


def test_downsample_simple():
    downsample = Downsample()
    magma_downsample = si.compile(downsample,
                                  file_name="tests/build/si_downsample.v")

    tester = fault.Tester(magma_downsample, magma_downsample.CLK)
    tester.poke(magma_downsample.data_in_valid, 0)
    tester.poke(magma_downsample.data_in_data, 0xDEAD)
    tester.poke(magma_downsample.data_out_ready, 0)
    tester.step(2)
    tester.expect(magma_downsample.data_out_valid, 0)
    tester.expect(magma_downsample.data_in_ready, 0)
    tester.step(2)
    tester.expect(magma_downsample.data_out_valid, 0)
    tester.expect(magma_downsample.data_in_ready, 0)
    tester.step(2)
    tester.expect(magma_downsample.data_out_valid, 0)
    tester.expect(magma_downsample.data_in_ready, 0)
    tester.poke(magma_downsample.data_in_valid, 1)
    tester.step(2)
    tester.poke(magma_downsample.data_out_ready, 1)
    tester.eval()
    tester.expect(magma_downsample.data_out_valid, 1)
    tester.expect(magma_downsample.data_in_ready, 1)
    tester.expect(magma_downsample.data_out_data, 0xDEAD)
    tester.step(2)
    tester.expect(magma_downsample.data_out_valid, 0)
    tester.step(2)
    tester.expect(magma_downsample.data_out_valid, 1)
    tester.expect(magma_downsample.data_out_data, 0xDEAD)

    tester.compile_and_run("verilator", flags=["-Wno-fatal"],
                           magma_output="verilog")

    verilog_downsample = m.DefineFromVerilogFile(
        "verilog/downsample.v", type_map={"CLK": m.In(m.Clock)})[0]
    verilog_tester = tester.retarget(verilog_downsample,
                                     verilog_downsample.CLK)
    verilog_tester.compile_and_run(target="verilator",
                                   flags=['-Wno-fatal'],
                                   include_directories=["../../verilog"],
                                   magma_output="verilog")


def test_downsample_loops_simple():
    downsample = Downsample()
    magma_downsample = si.compile(downsample,
                                  file_name="tests/build/si_downsample.v")

    tester = fault.Tester(magma_downsample, magma_downsample.CLK)
    for i in range(2):
        for y in range(32):
            for x in range(32):
                tester.poke(magma_downsample.data_in_valid, 1)
                tester.poke(magma_downsample.data_in_data, y * 32 + x)
                tester.poke(magma_downsample.data_out_ready, 1)
                tester.eval()
                tester.expect(magma_downsample.data_out_data, y * 32 + x)
                tester.expect(magma_downsample.data_out_valid, (y % 2 == 0) &
                                                               (x % 2 == 0))
                tester.expect(magma_downsample.data_in_ready, 1)
                tester.step(2)
                tester.poke(magma_downsample.data_in_valid, 0)
                tester.poke(magma_downsample.data_out_ready, 0)
                tester.eval()
                tester.expect(magma_downsample.data_out_valid, 0)
                tester.step(2)

    tester.compile_and_run("verilator", flags=["-Wno-fatal"],
                           magma_output="verilog")

    verilog_downsample = m.DefineFromVerilogFile(
        "verilog/downsample.v", type_map={"CLK": m.In(m.Clock)})[0]
    verilog_tester = tester.retarget(verilog_downsample,
                                     verilog_downsample.CLK)
    verilog_tester.compile_and_run(target="verilator",
                                   flags=['-Wno-fatal'],
                                   include_directories=["../../verilog"],
                                   magma_output="verilog")


def test_downsample_loops_simple_random_stalls():
    downsample = Downsample()
    magma_downsample = si.compile(downsample,
                                  file_name="tests/build/si_downsample.v")

    tester = fault.Tester(magma_downsample, magma_downsample.CLK)
    for i in range(2):
        for y in range(32):
            for x in range(32):
                while True:
                    in_valid = random.getrandbits(1)
                    tester.poke(magma_downsample.data_in_valid, in_valid)
                    tester.poke(magma_downsample.data_in_data, y * 32 + x)
                    out_ready = random.getrandbits(1)
                    tester.poke(magma_downsample.data_out_ready, out_ready)
                    tester.eval()
                    tester.expect(magma_downsample.data_out_data, y * 32 + x)
                    tester.expect(magma_downsample.data_out_valid,
                                  (y % 2 == 0) & (x % 2 == 0) &
                                  in_valid)
                    tester.expect(magma_downsample.data_in_ready, out_ready)
                    tester.step(2)
                    if in_valid & out_ready:
                        break

    tester.compile_and_run("verilator", flags=["-Wno-fatal"],
                           magma_output="verilog")

    verilog_downsample = m.DefineFromVerilogFile(
        "verilog/downsample.v", type_map={"CLK": m.In(m.Clock)})[0]
    verilog_tester = tester.retarget(verilog_downsample,
                                     verilog_downsample.CLK)
    verilog_tester.compile_and_run(target="verilator",
                                   flags=['-Wno-fatal'],
                                   include_directories=["../../verilog"],
                                   magma_output="verilog")
