#
# Copyright (c) 2004-2005 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
# This component and the accompanying materials are made available
# under the terms of "Eclipse Public License v1.0"
# which accompanies this distribution, and is available
# at the URL "http://www.eclipse.org/legal/epl-v10.html".
#
# Initial Contributors:
# Nokia Corporation - initial contribution.
#
# Contributors:
#
# Description:  Makefile to generate icon file for Video
#               Telephone application.
#

ifeq (WINS,$(findstring WINS, $(PLATFORM)))
ZDIR=\epoc32\release\$(PLATFORM)\$(CFG)\z
else
ZDIR=\epoc32\data\z
endif

TARGETDIR=$(ZDIR)\resource\apps
HEADERDIR=\epoc32\include
ICONTARGETFILENAME=$(TARGETDIR)\videotelui.mif
HEADERFILENAME=$(HEADERDIR)\videotelui.mbg

do_nothing :
	@rem do_nothing

MAKMAKE : do_nothing

BLD : do_nothing

CLEAN : do_nothing

LIB : do_nothing

CLEANLIB : do_nothing

# ----------------------------------------------------------------------------
# NOTE 1: DO NOT DEFINE MASK FILE NAMES! They are included automatically by
# MifConv if the mask detph is defined.
#
# NOTE 2: Usually, source paths should not be included in the bitmap
# definitions. MifConv searches for the icons in all icon directories in a
# predefined order, which is currently \s60\icons, \s60\bitmaps2.
# The directory \s60\icons is included in the search only if the feature flag
# __SCALABLE_ICONS is defined.
# ----------------------------------------------------------------------------
RESOURCE :
	mifconv $(ICONTARGETFILENAME) /h$(HEADERFILENAME) \
        /c8,8 qgn_graf_call_video_out_bg.bmp \
        /c8 qgn_indi_call_video_blind_in.bmp \
        /c8 qgn_indi_call_video_blind_out.bmp \
        /1 qgn_graf_zoom_area.bmp \
        /c8,1 qgn_indi_zoom_dir.bmp \
        /c8 qgn_indi_zoom_min.bmp \
        /c8 qgn_indi_zoom_max.bmp \
        /8 qgn_indi_call_video_blind_in_mask_icon.bmp \
        /8 qgn_indi_call_video_blind_out_mask_icon.bmp \
        /c8,8 qgn_indi_tb_camera_main.bmp \
        /c8,8 qgn_indi_tb_camera_secondary.bmp \
        /c8,8 qgn_indi_tb_gallery.bmp \
        /c8,8 qgn_indi_tb_microphone_mute.bmp \
        /c8,8 qgn_indi_tb_microphone_unmute.bmp \
        /c8,8 qgn_indi_tb_swap_images.bmp \
        /c8,8 qgn_indi_tb_video.bmp \
        /c8,8 qgn_indi_tb_video_disable.bmp \
        /c8,8 qgn_indi_tb_zoom.bmp \
        /c8,8 qgn_indi_cams_tb_capture.bmp \
        /c8,8 qgn_indi_tb_ihf_on.bmp \
        /c8,8 qgn_indi_tb_handset.bmp \
        /c8,8 qgn_indi_tb_bthf.bmp


FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo $(HEADERFILENAME)&& \
    @echo $(ICONTARGETFILENAME)

FINAL : do_nothing

# End of File
