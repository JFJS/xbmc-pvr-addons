#pragma once
/*
 *      Copyright (C) 2010 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include <inttypes.h>
#include "client.h"

uint64_t ntohll(uint64_t a);
uint64_t htonll(uint64_t a);

#include "libXBMC_codec.h"

class CodecDescriptor
{
public:
  CodecDescriptor(void)
  {
    m_codec.codec_id   = XBMC_INVALID_CODEC_ID;
    m_codec.codec_type = XBMC_CODEC_TYPE_UNKNOWN;
  }

  CodecDescriptor(xbmc_codec_t codec, const char* name) :
    m_codec(codec),
    m_strName(name) {}
  virtual ~CodecDescriptor(void) {}

  const std::string& Name(void) const  { return m_strName; }
  xbmc_codec_t Codec(void) const { return m_codec; }

  static CodecDescriptor GetCodecByName(const char* strCodecName)
  {
    CodecDescriptor retVal;
    // some of Tvheadend's and VDR's codec names don't match ffmpeg's, so translate them to something ffmpeg understands
    if (!strcmp(strCodecName, "MPEG2AUDIO"))
      retVal = CodecDescriptor(CODEC->GetCodecByName("MP2"), strCodecName);
    else if (!strcmp(strCodecName, "MPEGTS"))
      retVal = CodecDescriptor(CODEC->GetCodecByName("MPEG2VIDEO"), strCodecName);
    else
      retVal = CodecDescriptor(CODEC->GetCodecByName(strCodecName), strCodecName);

    return retVal;
  }

private:
  xbmc_codec_t m_codec;
  std::string  m_strName;
};
