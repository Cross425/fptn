\
#pragma once
/*
 * OpenWrt uses OpenSSL 3.x, where SSL_CTX_set_keylog_callback may be unavailable.
 * When building with -DFPTN_DISABLE_OPENSSL_KEYLOG=ON, we force-include this header
 * to turn keylog into a no-op, avoiding link errors.
 */
#include <openssl/opensslv.h>
#include <openssl/ssl.h>

#ifndef FPTN_DISABLE_OPENSSL_KEYLOG
#define FPTN_DISABLE_OPENSSL_KEYLOG 1
#endif

/* If the symbol is missing at link time, make the call a no-op. */
#ifndef SSL_CTX_set_keylog_callback
#define SSL_CTX_set_keylog_callback(ctx, cb) ((void)0)
#endif
