/* Capstone Disassembly Engine */
/* By Spike, xwings 2019 */

#ifdef CAPSTONE_HAS_WASM

#include <string.h>

#include "../../cs_priv.h"
#include "../../utils.h"

#include "WASMMapping.h"

// fill in details
void WASM_get_insn_id(cs_struct *h, cs_insn *insn, unsigned int id)
{
	insn->id = id;
}

#ifndef CAPSTONE_DIET
static const name_map insn_name_maps[256] = {
	{ WASM_INS_UNREACHABLE, "unreachable" },
	{ WASM_INS_NOP, "nop" },
	{ WASM_INS_BLOCK, "block" },
	{ WASM_INS_LOOP, "loop" },
	{ WASM_INS_IF, "if" },
	{ WASM_INS_ELSE, "else" },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_END, "end" },
	{ WASM_INS_BR, "br" },
	{ WASM_INS_BR_IF, "br_if" },
	{ WASM_INS_BR_TABLE, "br_table" },
	{ WASM_INS_RETURN, "return" },
	{ WASM_INS_CALL, "call" },
	{ WASM_INS_CALL_INDIRECT, "call_indirect" },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_DROP, "drop" },
	{ WASM_INS_SELECT, "select" },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_GET_LOCAL, "get_local" },
	{ WASM_INS_SET_LOCAL, "set_local" },
	{ WASM_INS_TEE_LOCAL, "tee_local" },
	{ WASM_INS_GET_GLOBAL, "get_global" },
	{ WASM_INS_SET_GLOBAL, "set_global" },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_I32_LOAD, "i32.load" },
	{ WASM_INS_I64_LOAD, "i64.load" },
	{ WASM_INS_F32_LOAD, "f32.load" },
	{ WASM_INS_F64_LOAD, "f64.load" },
	{ WASM_INS_I32_LOAD8_S, "i32.load8_s" },
	{ WASM_INS_I32_LOAD8_U, "i32.load8_u" },
	{ WASM_INS_I32_LOAD16_S, "i32.load16_s" },
	{ WASM_INS_I32_LOAD16_U, "i32.load16_u" },
	{ WASM_INS_I64_LOAD8_S, "i64.load8_s" },
	{ WASM_INS_I64_LOAD8_U, "i64.load8_u" },
	{ WASM_INS_I64_LOAD16_S, "i64.load16_s" },
	{ WASM_INS_I64_LOAD16_U, "i64.load16_u"},
	{ WASM_INS_I64_LOAD32_S, "i64.load32_s"},
	{ WASM_INS_I64_LOAD32_U, "i64.load32_u" },
	{ WASM_INS_I32_STORE, "i32.store" },
	{ WASM_INS_I64_STORE, "i64.store" },
	{ WASM_INS_F32_STORE, "f32.store" },
	{ WASM_INS_F64_STORE, "f64.store" },
	{ WASM_INS_I32_STORE8, "i32.store8" },
	{ WASM_INS_I32_STORE16, "i32.store16" },
	{ WASM_INS_I64_STORE8, "i64.store8" },
	{ WASM_INS_I64_STORE16, "i64.store16" },
	{ WASM_INS_I64_STORE32, "i64.store32" },
	{ WASM_INS_CURRENT_MEMORY, "current_memory" },
	{ WASM_INS_GROW_MEMORY, "grow_memory" },
	{ WASM_INS_I32_CONST, "i32.const" },
	{ WASM_INS_I64_CONST, "i64.const" },
	{ WASM_INS_F32_CONST, "f32.const" },
	{ WASM_INS_F64_CONST, "f64.const" },
	{ WASM_INS_I32_EQZ, "i32.eqz" },
	{ WASM_INS_I32_EQ, "i32.eq" },
	{ WASM_INS_I32_NE, "i32.ne" },
	{ WASM_INS_I32_LT_S, "i32.lt_s" },
	{ WASM_INS_I32_LT_U, "i32.lt_u" },
	{ WASM_INS_I32_GT_S, "i32.gt_s" },
	{ WASM_INS_I32_GT_U, "i32.gt_u" },
	{ WASM_INS_I32_LE_S, "i32.le_s" },
	{ WASM_INS_I32_LE_U, "i32.le_u" },
	{ WASM_INS_I32_GE_S, "i32.ge_s" },
	{ WASM_INS_I32_GE_U, "i32.ge_u" },
	{ WASM_INS_I64_EQZ, "i64.eqz" },
	{ WASM_INS_I64_EQ, "i64.eq" },
	{ WASM_INS_I64_NE, "i64.ne" },
	{ WASM_INS_I64_LT_S, "i64.lt_s" },
	{ WASM_INS_I64_LT_U, "i64.lt_u" },
	{ WASN_INS_I64_GT_S, "i64.gt_s" },
	{ WASM_INS_I64_GT_U, "i64.gt_u" },
	{ WASM_INS_I64_LE_S, "i64.le_s" },
	{ WASM_INS_I64_LE_U, "i64.le_u" },
	{ WASM_INS_I64_GE_S, "i64.ge_s" },
	{ WASM_INS_I64_GE_U, "i64.ge_u" },
	{ WASM_INS_F32_EQ, "f32.eq" },
	{ WASM_INS_F32_NE, "f32.ne" },
	{ WASM_INS_F32_LT, "f32.lt" },
	{ WASM_INS_F32_GT, "f32.gt" },
	{ WASM_INS_F32_LE, "f32.le" },
	{ WASM_INS_F32_GE, "f32.ge" },
	{ WASM_INS_F64_EQ, "f64.eq" },
	{ WASM_INS_F64_NE, "f64.ne" },
	{ WASM_INS_F64_LT, "f64.lt" },
	{ WASM_INS_F64_GT, "f64.gt" },
	{ WASM_INS_F64_LE, "f64.le" },
	{ WASM_INS_F64_GE, "f64.ge" },
	{ WASM_INS_I32_CLZ, "i32.clz" },
	{ WASM_INS_I32_CTZ, "i32.ctz" },
	{ WASM_INS_I32_POPCNT, "i32.popcnt" },
	{ WASM_INS_I32_ADD, "i32.add" },
	{ WASM_INS_I32_SUB, "i32.sub" },
	{ WASM_INS_I32_MUL, "i32.mul" },
	{ WASM_INS_I32_DIV_S, "i32.div_s" },
	{ WASM_INS_I32_DIV_U, "i32.div_u" },
	{ WASM_INS_I32_REM_S, "i32.rem_s" },
	{ WASM_INS_I32_REM_U, "i32.rem_u" },
	{ WASM_INS_I32_AND, "i32.and" },
	{ WASM_INS_I32_OR, "i32.or" },
	{ WASM_INS_I32_XOR, "i32.xor" },
	{ WASM_INS_I32_SHL, "i32.shl" },
	{ WASM_INS_I32_SHR_S, "i32.shr_s" },
	{ WASM_INS_I32_SHR_U, "i32.shr_u" },
	{ WASM_INS_I32_ROTL, "i32.rotl" },
	{ WASM_INS_I32_ROTR, "i32.rotr" },
	{ WASM_INS_I64_CLZ, "i64.clz" },
	{ WASM_INS_I64_CTZ, "i64.ctz" },
	{ WASM_INS_I64_POPCNT, "i64.popcnt" },
	{ WASM_INS_I64_ADD, "i64.add" },
	{ WASM_INS_I64_SUB, "i64.sub" },
	{ WASM_INS_I64_MUL, "i64.mul" },
	{ WASM_INS_I64_DIV_S, "i64.div_s" },
	{ WASM_INS_I64_DIV_U, "i64.div_u" },
	{ WASM_INS_I64_REM_S, "i64.rem_s" },
	{ WASM_INS_I64_REM_U, "i64.rem_u" },
	{ WASM_INS_I64_AND, "i64.and" },
	{ WASM_INS_I64_OR, "i64.or" },
	{ WASM_INS_I64_XOR, "i64.xor" },
	{ WASM_INS_I64_SHL, "i64.shl" },
	{ WASM_INS_I64_SHR_S, "i64.shr_s" },
	{ WASM_INS_I64_SHR_U, "i64.shr_u" },
	{ WASM_INS_I64_ROTL, "i64.rotl" },
	{ WASM_INS_I64_ROTR, "i64.rotr" },
	{ WASM_INS_F32_ABS, "f32.abs" },
	{ WASM_INS_F32_NEG, "f32.neg" },
	{ WASM_INS_F32_CEIL, "f32.ceil" },
	{ WASM_INS_F32_FLOOR, "f32.floor" },
	{ WASM_INS_F32_TRUNC, "f32.trunc" },
	{ WASM_INS_F32_NEAREST, "f32.nearest" },
	{ WASM_INS_F32_SQRT, "f32.sqrt" },
	{ WASM_INS_F32_ADD, "f32.add" },
	{ WASM_INS_F32_SUB, "f32.sub" },
	{ WASM_INS_F32_MUL, "f32.mul" },
	{ WASM_INS_F32_DIV, "f32.div" },
	{ WASM_INS_F32_MIN, "f32.min" },
	{ WASM_INS_F32_MAX, "f32.max" },
	{ WASM_INS_F32_COPYSIGN, "f32.copysign" },
	{ WASM_INS_F64_ABS, "f64.abs" },
	{ WASM_INS_F64_NEG, "f64.neg" },
	{ WASM_INS_F64_CEIL, "f64.ceil" },
	{ WASM_INS_F64_FLOOR, "f64.floor" },
	{ WASM_INS_F64_TRUNC, "f64.trunc" },
	{ WASM_INS_F64_NEAREST, "f64.nearest" },
	{ WASM_INS_F64_SQRT, "f64.sqrt" },
	{ WASM_INS_F64_ADD, "f64.add" },
	{ WASM_INS_F64_SUB, "f64.sub" },
	{ WASM_INS_F64_MUL, "f64.mul" },
	{ WASM_INS_F64_DIV, "f64.div" },
	{ WASM_INS_F64_MIN, "f64.min" },
	{ WASM_INS_F64_MAX, "f64.max" },
	{ WASM_INS_F64_COPYSIGN, "f64.copysign" },
	{ WASM_INS_I32_WARP_I64, "i32.warp/i64" },
	{ WASP_INS_I32_TRUNC_S_F32, "i32.trunc_s/f32" },
	{ WASM_INS_I32_TRUNC_U_F32, "i32.trunc_u/f32" },
	{ WASM_INS_I32_TRUNC_S_F64, "i32/trunc_s/f64" },
	{ WASM_INS_I32_TRUNC_U_F64, "i32/trunc_u/f64" },
	{ WASM_INS_I64_EXTEND_S_I32, "i64/extend_s/i32" },
	{ WASM_INS_I64_EXTEND_U_I32, "i64/extend_u/i32" },
	{ WASM_INS_I64_TRUNC_S_F32, "i64.trunc_s/f32" },
	{ WASM_INS_I64_TRUNC_U_F32, "i64.trunc_u/f32" },
	{ WASM_INS_I64_TRUNC_S_F64, "f64.trunc_s/f64" },
	{ WASM_INS_I64_TRUNC_U_F64, "f64.trunc_u/f64" },
	{ WASM_INS_F32_CONVERT_S_I32, "f32.convert_s/i32" },
	{ WASM_INS_F32_CONVERT_U_I32, "f32.convert_u/i32" },
	{ WASM_INS_F32_CONVERT_S_I64, "f32.convert_s/i64" },
	{ WASM_INS_F32_CONVERT_U_I64, "f32.convert_u/i64" },
	{ WASM_INS_F32_DEMOTE_F64, "f32.demote/f64" },
	{ WASM_INS_F64_CONVERT_S_I32, "f64.convert_s/i32" },
	{ WASM_INS_F64_CONVERT_U_I32, "f64.convert_u/i32" },
	{ WASM_INS_F64_CONVERT_S_I64, "f64.convert_s/i64" },
	{ WASM_INS_F64_CONVERT_U_I64, "f64.convert_u/i64" },
	{ WASM_INS_F64_PROMOTE_F32, "f64.promote/f32" },
	{ WASM_INS_I32_REINTERPRET_F32, "i32.reinterpret/f32" },
	{ WASM_INS_I64_REINTERPRET_F64, "i64.reinterpret/f64" },
	{ WASM_INS_F32_REINTERPRET_I32, "f32.reinterpret/i32" },
	{ WASM_INS_F64_REINTERPRET_I64, "f64.reinterpret/i64" },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
	{ WASM_INS_INVALID, NULL },
};
#endif

const char *WASM_insn_name(csh handle, unsigned int id)
{
#ifndef CAPSTONE_DIET
	if (id >= ARR_SIZE(insn_name_maps))
		return NULL;
	else
		return insn_name_maps[id].name;
#else
	return NULL;
#endif
}

#ifndef CAPSTONE_DIET
static const name_map group_name_maps[] = {
	// generic groups
	{ WASM_GRP_INVALID, NULL },
	// special groups
	{ WASM_GRP_NUMBERIC, "numberic"},
	{ WASM_GRP_PARAMETRIC, "parametric"},
	{ WASM_GRP_VARIABLE, "variable"},
	{ WASM_GRP_MEMORY, "memory"},
	{ WASM_GRP_CONTROL, "control"},
};
#endif

#ifndef CAPSTONE_DIET
static const name_map kind_name_maps[] = {
	{ WASM_OP_INVALID, "Invalid" },
	{ WASM_OP_NONE, "None" },
	{ WASM_OP_INT7, "uint7" },
	{ WASM_OP_VARUINT32, "varuint32" },
	{ WASM_OP_VARUINT64, "varuint64" },
	{ WASM_OP_UINT32, "uint32" },
	{ WASM_OP_UINT64, "uint64" },
};
#endif

const char *WASM_kind_name(unsigned int id){
#ifndef CAPSTONE_DIET
	return id2name(kind_name_maps, ARR_SIZE(kind_name_maps), id);
#else
	return NULL;
#endif
}

const char *WASM_group_name(csh handle, unsigned int id)
{
#ifndef CAPSTONE_DIET
	return id2name(group_name_maps, ARR_SIZE(group_name_maps), id);
#else
	return NULL;
#endif
}
#endif