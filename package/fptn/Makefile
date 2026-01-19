include $(TOPDIR)/rules.mk

PKG_NAME:=fptn
PKG_VERSION:=0.3.35
PKG_RELEASE:=7

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/batchar2/fptn.git
PKG_SOURCE_VERSION:=v$(PKG_VERSION)

PKG_LICENSE:=MIT

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/fptn
  SECTION:=net
  CATEGORY:=Network
  TITLE:=FPTN client (OpenWrt)
  DEPENDS:=\
    +libstdcpp \
    +libopenssl \
    +libpthread \
    +zlib \
    +protobuf \
    +libprotobuf \
    +libatomic \
    +libcurl \
    +libuv \
    +kmod-tun \
    +ca-bundle
endef

define Package/fptn/description
  FPTN VPN client for OpenWrt (client-only, OpenSSL + Protobuf + cURL + libuv).
endef

CMAKE_OPTIONS += \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_CLIENT_CLI=ON \
  -DBUILD_SERVER=OFF \
  -DBUILD_GUI=OFF \
  -DBUILD_TESTS=OFF \
  -DUSE_CONAN=OFF \
  -DUSE_BORINGSSL=OFF \
  -DProtobuf_USE_STATIC_LIBS=OFF \
  -Dprotobuf_MODULE_COMPATIBLE=ON

define Package/fptn/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/fptn-client $(1)/usr/sbin/fptn

	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/fptn.init $(1)/etc/init.d/fptn
endef

$(eval $(call BuildPackage,fptn))
