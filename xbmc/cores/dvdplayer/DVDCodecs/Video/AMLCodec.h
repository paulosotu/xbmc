#pragma once
/*
 *      Copyright (C) 2005-2011 Team XBMC
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

#include "DVDVideoCodec.h"
#include "cores/dvdplayer/DVDStreamInfo.h"
#include "cores/VideoRenderers/RenderFeatures.h"
#include "guilib/Geometry.h"
#include "threads/Thread.h"

typedef struct am_private_t am_private_t;

class DllLibAmCodec;

class CAMLCodec : public CThread
{
public:
  CAMLCodec();
  virtual ~CAMLCodec();

  bool          OpenDecoder(CDVDStreamInfo &hints);
  void          CloseDecoder();
  void          Reset();

  int           Decode(unsigned char *pData, size_t size, double dts, double pts);

  bool          GetPicture(DVDVideoPicture* pDvdVideoPicture);
  void          SetSpeed(int speed);
  int           GetDataSize();
  double        GetTimeSize();

protected:
  virtual void  Process();

private:
  double        GetPlayerPtsSeconds();
  void          SetVideoPtsSeconds(double pts);
  void          ShowMainVideo(const bool show);
  void          SetVideoZoom(const float zoom);
  void          SetVideoContrast(const int contrast);
  void          SetVideoBrightness(const int brightness);
  void          SetVideoSaturation(const int saturation);
  void          GetRenderFeatures(Features &renderFeatures);
  static void   RenderFeaturesCallBack(const void *ctx, Features &renderFeatures);
  void          SetVideoRect(const CRect &SrcRect, const CRect &DestRect);
  static void   RenderUpdateCallBack(const void *ctx, const CRect &SrcRect, const CRect &DestRect);

  DllLibAmCodec   *m_dll;
  bool             m_opened;
  am_private_t    *am_private;
  CDVDStreamInfo   m_hints;
  volatile int     m_speed;
  volatile int64_t m_1st_pts;
  volatile int64_t m_cur_pts;
  volatile int64_t m_cur_pictcnt;
  volatile int64_t m_old_pictcnt;
  volatile double  m_timesize;
  volatile int64_t m_vbufsize;
  int64_t          m_start_dts;
  int64_t          m_start_pts;
  CEvent           m_ready_event;

  CRect            m_dst_rect;
  int              m_view_mode;
  float            m_zoom;
  int              m_contrast;
  int              m_brightness;
};