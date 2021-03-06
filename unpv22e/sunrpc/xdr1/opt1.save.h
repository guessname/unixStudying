/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _OPT1_H_RPCGEN
#define	_OPT1_H_RPCGEN

#include <rpc/rpc.h>

#ifdef __cplusplus
extern "C" {
#endif


/* include opt1h */
struct optlong {
	int flag;
	union {
		long val;
	} optlong_u;
};
typedef struct optlong optlong;

struct args {
	optlong arg1;
	struct {
		u_int arg2_len;
		long *arg2_val;
	} arg2;
	long *arg3;
};
typedef struct args args;
/* end opt1h */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_optlong(XDR *, optlong*);
extern  bool_t xdr_args(XDR *, args*);

#else /* K&R C */
extern bool_t xdr_optlong();
extern bool_t xdr_args();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_OPT1_H_RPCGEN */
