# OpenWrt package Makefile (fix OpenSSL detection)

include $(TOPDIR)/rules.mk

PKG_NAME:=fptn
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/fptn
  SECTION:=net
  CATEGORY:=Network
  TITLE:=fptn
  DEPENDS:=+libopenssl3
endef

CMAKE_OPTIONS +=   -DFPTN_NO_FETCHCONTENT=ON   -DFPTN_DISABLE_WERROR=ON   -DFPTN_DISABLE_OPENSSL_KEYLOG=ON   -DOPENSSL_ROOT_DIR=$(STAGING_DIR)/usr   -DOPENSSL_INCLUDE_DIR=$(STAGING_DIR)/usr/include   -DOPENSSL_CRYPTO_LIBRARY=$(STAGING_DIR)/usr/lib/libcrypto.so   -DOPENSSL_SSL_LIBRARY=$(STAGING_DIR)/usr/lib/libssl.so

$(eval $(call BuildPackage,fptn))