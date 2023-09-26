/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : player.h
 * PURPOSE     : Animation project.
 *               Tracks player class declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Vitaly A. Galinsky.
 * LAST UPDATE : 31.07.2021.
 * NOTE        : Module namespace 'nigl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __player_h_
#define __player_h_

#include "../def.h"

namespace nigl
{
  class sound
  {
  private:
    VOID *mem;
    INT format;
    UINT size, freq;
    CHAR loop;
    UINT buffer, source;

    FLT speed;
    FLT volume;
    BOOL IsLoop;
  public:
    BOOL IsPlaying;
    BOOL IsStopped;


    sound( const std::string Filename = "" ) : mem(nullptr), format(0), size(0), freq(0),  loop(0), IsLoop(FALSE), speed(1.0), volume(0.1), IsPlaying(FALSE)
    {
      alGenBuffers(1, &buffer);

      if (Filename != "")
      {
        alutLoadWAVFile((ALbyte *)Filename.c_str(), &format, &mem, &size, &freq, &loop);
        alBufferData(buffer, format, mem, size, freq);
        alutUnloadWAV(format, mem, size, freq);

        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
        alSourcef(source, AL_PITCH, speed);
        alSourcef(source, AL_GAIN, volume);
        alSourcei(source, AL_LOOPING, IsLoop);
      }
    }


    ~sound( VOID )
    {
      if (source != 0)
        alDeleteSources(1, &source), source = 0;
      if (buffer !=  0)
        alDeleteBuffers(1, &buffer), buffer = 0;

      mem = nullptr;
    }

    VOID Play( VOID )
    {
      if (source != 0)
        alSourcePlay(source);
      IsPlaying = TRUE;
    }

    VOID Pause( VOID )
    {
      if (source != 0)
        alSourcePause(source);
      IsPlaying = FALSE;
    }
  };
}

#endif /* __player_h */
