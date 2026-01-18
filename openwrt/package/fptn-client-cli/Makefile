include $(TOPDIR)/rules.mk

PKG_NAME:=fptn-client-cli
PKG_VERSION:=0.3.34
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/batchar2/fptn.git
PKG_SOURCE_VERSION:=master
PKG_MIRROR_HASH:=skip

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

PKG_BUILD_DEPENDS:=python3/host
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/fptn-client-cli
  SECTION:=net
  CATEGORY:=Network
  TITLE:=FPTN client CLI
  DEPENDS:=+libstdcpp +libpthread
endef

define Package/fptn-client-cli/description
  FPTN client CLI built with Conan+CMake, packaged for OpenWrt (apk/opkg).
endef

define Build/Configure
	# no-op: Conan+CMake in Build/Compile
endef

define Build/Compile
	which conan
	# Conan deps + build (expects Conan profile "openwrt-a53" created by workflow)
	cd $(PKG_BUILD_DIR) && \
	  conan install . \
	    --profile:host=openwrt-a53 \
	    --profile:build=default \
	    -o with_gui_client=False \
	    -o build_only_fptn_lib=False \
	    --build=missing
	cd $(PKG_BUILD_DIR) && \
	  cmake -S . -B build -G Ninja \
	    -DCMAKE_BUILD_TYPE=Release
	cmake --build $(PKG_BUILD_DIR)/build -j$(NPROC)
endef

define Package/fptn-client-cli/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/fptn-client-cli $(1)/usr/bin/fptn-client-cli
endef

$(eval $(call BuildPackage,fptn-client-cli))
