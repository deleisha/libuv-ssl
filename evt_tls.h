#ifndef EVT_TLS_H
#define EVT_TLS_H


#ifdef __cplusplus 
extern "C" {
#endif

#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/conf.h>
#include <openssl/engine.h>

#include "queue.h"


typedef struct evt_tls_s evt_tls_t;

typedef void (*evt_conn_cb)(evt_tls_t *con, int status);
typedef void (*evt_accept_cb)(evt_tls_t *con, int status);

struct evt_tls_s {
    BIO     *app_bio_; //Our BIO, All IO should be through this

    SSL     *ssl;

    int (*meta_hdlr)(evt_tls_t *c, void *edata, int len);
    evt_conn_cb connect_cb;
    evt_accept_cb accept_cb;

    BIO     *ssl_bio_; //the ssl BIO used only by openSSL

    QUEUE q;

};


typedef struct evt_ctx_s
{
    //find better place for it , should be one time init
    SSL_CTX *ctx;

    //flags which tells if cert is set
    int cert_set;

    //flags which tells if key is set
    int key_set;

    //flag to signify if ssl error has occured
    int ssl_err_;

    void *live_con[2];
} evt_ctx_t;


//supported TLS operation
enum tls_op_type {
    EVT_TLS_OP_HANDSHAKE
   ,EVT_TLS_OP_READ
   ,EVT_TLS_OP_WRITE
   ,EVT_TLS_OP_SHUTDOWN
};

/*configure the tls state machine */
int evt_ctx_init(evt_ctx_t *tls);

/* set the certifcate and key in order */
int evt_ctx_set_crt_key(evt_ctx_t *tls, char *crtf, char *key);

/* test if the certificate */
int evt_ctx_is_crtf_set(evt_ctx_t *t);

/* test if the key is set */
int evt_ctx_is_key_set(evt_ctx_t *t);

evt_tls_t *getSSL(evt_ctx_t *d_eng);

int evt_tls_feed_data(evt_tls_t *c, void *data, int sz);
int after__wrk(evt_tls_t *c, void *buf);
int evt__ssl_op(evt_tls_t *c, enum tls_op_type op, void *buf, int *sz);
int evt_tls_connect(evt_tls_t *con, evt_conn_cb cb);
void evt_tls_set_nio(evt_tls_t *c, int (*fn)(evt_tls_t *t, void *data, int sz));


#ifdef __cplusplus 
}
#endif

#endif //define EVT_TLS_H
