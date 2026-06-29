require conf/distro/include/distro_features.inc
require conf/distro/include/non-gplv3-license.inc

DISTROOVERRIDES =. "${@ 'qcom-auto-distro:' if d.getVar('DISTRO') != 'qcom-auto-distro' else ''}"

# Retain existing directory structure for msm or mdm distro images.
# Append variants like '-perf', '-user' etc to deploy dir.
DEPLOY_NAME_BASE = "${MACHINE}${@bb.utils.contains_any('DISTRO', 'msm mdm', '', '-' + d.getVar('DISTRO'), d)}"
DEPLOY_NAME = "${DEPLOY_NAME_BASE}${@['-' + (d.getVar('VARIANT') or ''), ''][not d.getVar('VARIANT') or d.getVar('VARIANT') == 'debug']}"
DEPLOY_DIR_IMAGE = "${DEPLOY_DIR}/images/${DEPLOY_NAME}"

# Static Users for QTI
USERADDEXTENSION ?= "useradd-staticids"
USERADD_UID_TABLES:prepend = "files/qti_passwd "
USERADD_GID_TABLES:prepend = "files/qti_group "

# Enable performance features
PERF_BUILD = "${@['0', '1'][d.getVar('VARIANT', True) != ('' or 'debug')]}"

# Build optimization to disable debugging features, mainly for production images.
USER_BUILD = "${@['0', '1'][d.getVar('VARIANT', True) == 'user']}"

# Use systemd init manager for system initialization.
INIT_MANAGER = "systemd"

