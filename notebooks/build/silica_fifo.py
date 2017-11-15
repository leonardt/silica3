from magma import *
import os
os.environ["MANTLE"] = os.getenv("MANTLE", "coreir")
from mantle import *
import mantle.common.operator


@cache_definition
def DefineSilicaMux(height, width):
    if "one-hot" == "one-hot":
        if width is None:
            T = Bit
        else:
            T = Bits(width)
        inputs = []
        for i in range(height):
            inputs += [f"I{i}", In(T)]
        class OneHotMux(Circuit):
            name = "SilicaOneHotMux{}{}".format(height, width)
            IO = inputs + ["S", In(Bits(height)), "O", Out(T)]
            @classmethod
            def definition(io):
                or_ = Or(height, width)
                wire(io.O, or_.O)
                for i in range(height):
                    and_ = And(2, width)
                    wire(and_.I0, getattr(io, f"I{i}"))
                    if width is not None:
                        for j in range(width):
                            wire(and_.I1[j], io.S[i])
                    else:
                        wire(and_.I1, io.S[i])
                    wire(getattr(or_, f"I{i}"), and_.O)
        return OneHotMux
    else:
        raise NotImplementedError()


Fifo = DefineCircuit("Fifo", "rdata", Out(Bits(4)), "empty", Out(Bit), "full", Out(Bit), "wdata", In(Bits(4)), "wen", In(Bit), "ren", In(Bit), *ClockInterface(has_ce=False))
Buffer = DefineCircuit("__silica_BufferFifo", "I", In(Bits(8)), "O", Out(Bits(8)))
wire(Buffer.I, Buffer.O)
EndDefine()
__silica_path_state = Buffer()

import types
def generate_fsm_mux(next, width, reg, path_state, output=False):
    if hasattr(width, "__len__"):  # Hack to check for tuple since magma overrides it
        filtered_next = []
        for curr, state in next:
            if curr[0] is None:
                assert all(not x for x in curr)
            else:
                filtered_next.append((curr, state))
        if len(filtered_next) == 2:
            muxs = [DefineMux(2, width[1])() for _ in range(width[0])]
        else:
            mux = DefineSilicaMux(len(filtered_next), width[1])()
        wire(mux.O, reg.wdata)
        CES = []
        for i, (input_, state) in enumerate(filtered_next):
            curr = list(filter(lambda x: x, curr))
            for j, input_ in enumerate(input_):
                if isinstance(input_, list):
                    input_ = bits(input_)
                wire(getattr(muxs[j], f"I{i}"), input_)
                if len(filtered_next) == 2:
                    if i == 0:
                        wire(muxs[j].S, path_state.O[state])
                else:
                    wire(muxs[j].S[i], path_state.O[state])
            CES.append(path_state.O[state])
        if len(CES) == 1:
            wire(CES[0], reg.wen)
    else:
        mux = DefineSilicaMux(len(next), width)()
        if output:
            wire(mux.O, reg)
        else:
            wire(mux.O, reg.I)
        for i, (input_, state) in enumerate(next):
            if isinstance(input_, list):
                input_ = bits(input_)
            wire(getattr(mux, f"I{i}"), input_)
            wire(mux.S[state], path_state.O[state])
__silica_yield_state = Register(2, init=1, has_ce=False)

wireclock(Fifo, __silica_yield_state)
wire(bits(1 << 1, 2), __silica_yield_state.I)
wdata = Fifo.wdata
wen = Fifo.wen
ren = Fifo.ren
next_full = DFF(has_ce=False, name="next_full", init=0)
wireclock(Fifo, next_full)
next_full_next = []
memory = DefineCoreirMem(4, 4)()
memory_next = []
memory_next_0_tmp = [None for _ in range(4)]
memory_next_1_tmp = [None for _ in range(4)]
memory_next_2_tmp = [None for _ in range(4)]
memory_next_3_tmp = [None for _ in range(4)]
memory_next_4_tmp = [None for _ in range(4)]
memory_next_5_tmp = [None for _ in range(4)]
memory_next_6_tmp = [None for _ in range(4)]
memory_next_7_tmp = [None for _ in range(4)]
next_empty = DFF(has_ce=False, name="next_empty", init=1)
wireclock(Fifo, next_empty)
next_empty_next = []
waddr = Register(2, has_ce=False)
wireclock(Fifo, waddr)
waddr_next = []
raddr = Register(2, has_ce=False)
wireclock(Fifo, raddr)
raddr_next = []
rdata_output = []
empty_output = []
full_output = []
next_full_next_0_tmp = next_full.O
next_empty_next_0_tmp = next_empty.O
waddr_next_0_tmp = [waddr.O[__silica_i] for __silica_i in range(2)]
raddr_next_0_tmp = [raddr.O[__silica_i] for __silica_i in range(2)]
full_0_tmp = next_full.O
empty_0_tmp = next_empty.O
rdata_0_tmp = memory.rdata
__silica_cond_0 = and_(wen, not_(full_0_tmp))
None
waddr_next_0_tmp = add(waddr.O, uint(1, 2))
next_full_next_0_tmp = eq(raddr.O, waddr_next_0_tmp)
next_empty_next_0_tmp = bit(False)
__silica_cond_1 = and_(ren, not_(empty_0_tmp))
raddr_next_0_tmp = add(raddr.O, uint(1, 2))
next_empty_next_0_tmp = eq(raddr_next_0_tmp, waddr_next_0_tmp)
next_full_next_0_tmp = bit(False)
next_full_next.append((next_full_next_0_tmp, 0))
memory_next.append((memory_next_0_tmp, 0))
next_empty_next.append((next_empty_next_0_tmp, 0))
waddr_next.append((waddr_next_0_tmp, 0))
raddr_next.append((raddr_next_0_tmp, 0))
rdata_output.append((rdata_0_tmp, 0))
empty_output.append((empty_0_tmp, 0))
full_output.append((full_0_tmp, 0))
wire(__silica_path_state.I[0], and_(__silica_yield_state.O[0], __silica_cond_0, __silica_cond_1))
next_full_next_1_tmp = next_full.O
next_empty_next_1_tmp = next_empty.O
waddr_next_1_tmp = [waddr.O[__silica_i] for __silica_i in range(2)]
raddr_next_1_tmp = [raddr.O[__silica_i] for __silica_i in range(2)]
full_1_tmp = next_full.O
empty_1_tmp = next_empty.O
rdata_1_tmp = memory.rdata
__silica_cond_2 = and_(wen, not_(full_1_tmp))
None
waddr_next_1_tmp = add(waddr.O, uint(1, 2))
next_full_next_1_tmp = eq(raddr.O, waddr_next_1_tmp)
next_empty_next_1_tmp = bit(False)
__silica_cond_3 = not_(and_(ren, not_(empty_1_tmp)))
next_full_next.append((next_full_next_1_tmp, 1))
memory_next.append((memory_next_1_tmp, 1))
next_empty_next.append((next_empty_next_1_tmp, 1))
waddr_next.append((waddr_next_1_tmp, 1))
raddr_next.append((raddr_next_1_tmp, 1))
rdata_output.append((rdata_1_tmp, 1))
empty_output.append((empty_1_tmp, 1))
full_output.append((full_1_tmp, 1))
wire(__silica_path_state.I[1], and_(__silica_yield_state.O[0], __silica_cond_2, __silica_cond_3))
next_full_next_2_tmp = next_full.O
next_empty_next_2_tmp = next_empty.O
waddr_next_2_tmp = [waddr.O[__silica_i] for __silica_i in range(2)]
raddr_next_2_tmp = [raddr.O[__silica_i] for __silica_i in range(2)]
full_2_tmp = next_full.O
empty_2_tmp = next_empty.O
rdata_2_tmp = memory.rdata
__silica_cond_4 = not_(and_(wen, not_(full_2_tmp)))
__silica_cond_5 = and_(ren, not_(empty_2_tmp))
raddr_next_2_tmp = add(raddr.O, uint(1, 2))
next_empty_next_2_tmp = eq(raddr_next_2_tmp, waddr.O)
next_full_next_2_tmp = bit(False)
next_full_next.append((next_full_next_2_tmp, 2))
memory_next.append((memory_next_2_tmp, 2))
next_empty_next.append((next_empty_next_2_tmp, 2))
waddr_next.append((waddr_next_2_tmp, 2))
raddr_next.append((raddr_next_2_tmp, 2))
rdata_output.append((rdata_2_tmp, 2))
empty_output.append((empty_2_tmp, 2))
full_output.append((full_2_tmp, 2))
wire(__silica_path_state.I[2], and_(__silica_yield_state.O[0], __silica_cond_4, __silica_cond_5))
next_full_next_3_tmp = next_full.O
next_empty_next_3_tmp = next_empty.O
waddr_next_3_tmp = [waddr.O[__silica_i] for __silica_i in range(2)]
raddr_next_3_tmp = [raddr.O[__silica_i] for __silica_i in range(2)]
full_3_tmp = next_full.O
empty_3_tmp = next_empty.O
rdata_3_tmp = memory.rdata
__silica_cond_6 = not_(and_(wen, not_(full_3_tmp)))
__silica_cond_7 = not_(and_(ren, not_(empty_3_tmp)))
next_full_next.append((next_full_next_3_tmp, 3))
memory_next.append((memory_next_3_tmp, 3))
next_empty_next.append((next_empty_next_3_tmp, 3))
waddr_next.append((waddr_next_3_tmp, 3))
raddr_next.append((raddr_next_3_tmp, 3))
rdata_output.append((rdata_3_tmp, 3))
empty_output.append((empty_3_tmp, 3))
full_output.append((full_3_tmp, 3))
wire(__silica_path_state.I[3], and_(__silica_yield_state.O[0], __silica_cond_6, __silica_cond_7))
next_full_next_4_tmp = next_full.O
next_empty_next_4_tmp = next_empty.O
waddr_next_4_tmp = [waddr.O[__silica_i] for __silica_i in range(2)]
raddr_next_4_tmp = [raddr.O[__silica_i] for __silica_i in range(2)]
full_4_tmp = next_full.O
empty_4_tmp = next_empty.O
rdata_4_tmp = memory.rdata
__silica_cond_8 = and_(wen, not_(full_4_tmp))
None
waddr_next_4_tmp = add(waddr.O, uint(1, 2))
next_full_next_4_tmp = eq(raddr.O, waddr_next_4_tmp)
next_empty_next_4_tmp = bit(False)
__silica_cond_9 = and_(ren, not_(empty_4_tmp))
raddr_next_4_tmp = add(raddr.O, uint(1, 2))
next_empty_next_4_tmp = eq(raddr_next_4_tmp, waddr_next_4_tmp)
next_full_next_4_tmp = bit(False)
next_full_next.append((next_full_next_4_tmp, 4))
memory_next.append((memory_next_4_tmp, 4))
next_empty_next.append((next_empty_next_4_tmp, 4))
waddr_next.append((waddr_next_4_tmp, 4))
raddr_next.append((raddr_next_4_tmp, 4))
rdata_output.append((rdata_4_tmp, 4))
empty_output.append((empty_4_tmp, 4))
full_output.append((full_4_tmp, 4))
wire(__silica_path_state.I[4], and_(__silica_yield_state.O[1], __silica_cond_8, __silica_cond_9))
next_full_next_5_tmp = next_full.O
next_empty_next_5_tmp = next_empty.O
waddr_next_5_tmp = [waddr.O[__silica_i] for __silica_i in range(2)]
raddr_next_5_tmp = [raddr.O[__silica_i] for __silica_i in range(2)]
full_5_tmp = next_full.O
empty_5_tmp = next_empty.O
rdata_5_tmp = memory.rdata
__silica_cond_10 = and_(wen, not_(full_5_tmp))
None
waddr_next_5_tmp = add(waddr.O, uint(1, 2))
next_full_next_5_tmp = eq(raddr.O, waddr_next_5_tmp)
next_empty_next_5_tmp = bit(False)
__silica_cond_11 = not_(and_(ren, not_(empty_5_tmp)))
next_full_next.append((next_full_next_5_tmp, 5))
memory_next.append((memory_next_5_tmp, 5))
next_empty_next.append((next_empty_next_5_tmp, 5))
waddr_next.append((waddr_next_5_tmp, 5))
raddr_next.append((raddr_next_5_tmp, 5))
rdata_output.append((rdata_5_tmp, 5))
empty_output.append((empty_5_tmp, 5))
full_output.append((full_5_tmp, 5))
wire(__silica_path_state.I[5], and_(__silica_yield_state.O[1], __silica_cond_10, __silica_cond_11))
next_full_next_6_tmp = next_full.O
next_empty_next_6_tmp = next_empty.O
waddr_next_6_tmp = [waddr.O[__silica_i] for __silica_i in range(2)]
raddr_next_6_tmp = [raddr.O[__silica_i] for __silica_i in range(2)]
full_6_tmp = next_full.O
empty_6_tmp = next_empty.O
rdata_6_tmp = memory.rdata
__silica_cond_12 = not_(and_(wen, not_(full_6_tmp)))
__silica_cond_13 = and_(ren, not_(empty_6_tmp))
raddr_next_6_tmp = add(raddr.O, uint(1, 2))
next_empty_next_6_tmp = eq(raddr_next_6_tmp, waddr.O)
next_full_next_6_tmp = bit(False)
next_full_next.append((next_full_next_6_tmp, 6))
memory_next.append((memory_next_6_tmp, 6))
next_empty_next.append((next_empty_next_6_tmp, 6))
waddr_next.append((waddr_next_6_tmp, 6))
raddr_next.append((raddr_next_6_tmp, 6))
rdata_output.append((rdata_6_tmp, 6))
empty_output.append((empty_6_tmp, 6))
full_output.append((full_6_tmp, 6))
wire(__silica_path_state.I[6], and_(__silica_yield_state.O[1], __silica_cond_12, __silica_cond_13))
next_full_next_7_tmp = next_full.O
next_empty_next_7_tmp = next_empty.O
waddr_next_7_tmp = [waddr.O[__silica_i] for __silica_i in range(2)]
raddr_next_7_tmp = [raddr.O[__silica_i] for __silica_i in range(2)]
full_7_tmp = next_full.O
empty_7_tmp = next_empty.O
rdata_7_tmp = memory.rdata
__silica_cond_14 = not_(and_(wen, not_(full_7_tmp)))
__silica_cond_15 = not_(and_(ren, not_(empty_7_tmp)))
next_full_next.append((next_full_next_7_tmp, 7))
memory_next.append((memory_next_7_tmp, 7))
next_empty_next.append((next_empty_next_7_tmp, 7))
waddr_next.append((waddr_next_7_tmp, 7))
raddr_next.append((raddr_next_7_tmp, 7))
rdata_output.append((rdata_7_tmp, 7))
empty_output.append((empty_7_tmp, 7))
full_output.append((full_7_tmp, 7))
wire(__silica_path_state.I[7], and_(__silica_yield_state.O[1], __silica_cond_14, __silica_cond_15))
wire(memory.raddr, (raddr).O)
wire(memory.waddr, waddr.O)
wire(memory.wdata, wdata)
wire(memory.wen, or_(__silica_path_state.O[0], __silica_path_state.O[1], __silica_path_state.O[4], __silica_path_state.O[5]))
generate_fsm_mux(next_full_next, None, next_full, __silica_path_state)
generate_fsm_mux(next_empty_next, None, next_empty, __silica_path_state)
generate_fsm_mux(waddr_next, 2, waddr, __silica_path_state)
generate_fsm_mux(raddr_next, 2, raddr, __silica_path_state)
generate_fsm_mux(rdata_output, 4, Fifo.rdata, __silica_path_state, output=True)
generate_fsm_mux(empty_output, None, Fifo.empty, __silica_path_state, output=True)
generate_fsm_mux(full_output, None, Fifo.full, __silica_path_state, output=True)
EndDefine()