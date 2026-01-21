include $(TOPDIR)/rules.mk

PKG_NAME:=fptn
PKG_VERSION:=git
PKG_RELEASE:=3

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/Cross425/fptn.git
PKG_SOURCE_VERSION:=bf92d82
PKG_MIRROR_HASH:=skip

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/fptn
  SECTION:=net
  CATEGORY:=Network
  TITLE:=fptn client (OpenWrt)
  DEPENDS:=+libstdcpp +libpthread +librt
endef

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release -DFPTN_NO_FETCHCONTENT=ON

define Build/Prepare
	$(call Build/Prepare/Default)
	cp -r ./vendor $(PKG_BUILD_DIR)/
endef

define Package/fptn/install
	$(INSTALL_DIR) $(1)/usr/bin
	# Universal install: copy any executable ELF binaries produced by build
	# from common staging/build locations.
	for f in \
		$(PKG_INSTALL_DIR)/usr/bin/* \
		$(PKG_INSTALL_DIR)/bin/* \
		$(PKG_BUILD_DIR)/build/* \
		$(PKG_BUILD_DIR)/bin/* \
		$(PKG_BUILD_DIR)/* ; do \
		[ -f "$$f" ] || continue; \
		[ -x "$$f" ] || continue; \
		# Avoid installing scripts/text; prefer ELF binaries.
		file "$$f" 2>/dev/null | grep -q "ELF" || continue; \
		$(INSTALL_BIN) "$$f" "$(1)/usr/bin/"; \
	done
endef

$(eval $(call BuildPackage,fptn))
