/* FILE NAME  : units.h
 * PROGRAMMER : ND4
 * LAST UPDATE: 24.07.2021
 * PURPOSE    : WinAPI preferences
 */

#ifndef __units_h_
#define __units_h_

#include "../anim/anim.h"

#pragma warning(disable: 26451)

namespace nigl
{
  /* Unit namespace */
  namespace units
  {
    class ctrl : public unit
    {
    private:
      model m3;
      matr ARCRotate;
      matr ARCTranslate;
      vec3 Dir;
      vec3 Right;
      vec3 Up;
      DBL 
        RotYAngle,
        RotZAngle,
        RotXAngle;

    public:
      ctrl( VOID )
      {
        //m3.Load("BIN/MODELS/ARC.g3dm");
        m3.Load("BIN/MODELS/ARC.g3dm");
        //gun.Load("BIN/MODELS/GUNS/G36/g36.g3dm");
        //gun.PrimLoad("BIN/MODELS/DLORE/AWP_Dragon_Lore.obj");
        ARCTranslate = matr::Translate(vec3(-3.3, 9.9, 0));
        ARCRotate = matr::Identity();
        RotYAngle = 0;
        RotZAngle = 0;
        RotXAngle = 0;
        m3.SetShader("ARC170");
      }

      ~ctrl( VOID ) override
      {
        //gun.PrimFree();
      }

      VOID Response( anim *Ani ) override
      {
        Dir = (Ani->Cam.At - Ani->Cam.Loc).Normalizing();
        Right = (Dir % vec3(0, 1, 0)).Normalizing();
        Up = (Right % Dir); /* Up */

        if (Ani->KeysClick['F'])
          Ani->FlipFullScreen();

        //if ((Ani->Keys['W'] || Ani->Keys['A'] || Ani->Keys['S'] || Ani->Keys['D']) && Ani->Keys[VK_CONTROL])
        //  Ani->Cam.Move(((Ani->Cam.Dir * ((Ani->Keys['W'] - Ani->Keys['S'])) +
        //                     Ani->Cam.Right * ((Ani->Keys['D'] - Ani->Keys['A']))) * 3000 * Ani->GlobalDeltaTime) * vec3(1, 0, 1));
        //if (Ani->Keys[VK_SPACE] || Ani->Keys[VK_LSHIFT])
        //  Ani->Cam.Move(mth::vec3<FLT>(0,
        //                                   ((Ani->Cam.Up * (Ani->Keys[VK_SPACE] - Ani->Keys[VK_LSHIFT])) * 3000 * Ani->GlobalDeltaTime)[1],
        //                                   0));
        
        //if (Ani->Keys[VK_RBUTTON] && Ani->Keys[VK_CONTROL])
        //{
        //  FLT Hp, Wp = Hp = Ani->Cam.ProjDist;
        //
        //  if (Ani->Cam.FrameW > Ani->Cam.FrameH)
        //    Wp *= static_cast<FLT>(Ani->Cam.FrameW) / Ani->Cam.FrameH;
        //  else
        //    Hp *= static_cast<FLT>(Ani->Cam.FrameH) / Ani->Cam.FrameW;
        //
        //  FLT Dist = !(Ani->Cam.At - Ani->Cam.Loc);
        //
        //  FLT sx = -Ani->Mdx * Wp / Ani->Cam.FrameW * Dist / Ani->Cam.ProjDist;
        //  FLT sy = Ani->Mdy * Hp / Ani->Cam.FrameH * Dist / Ani->Cam.ProjDist;
        //
        //  Ani->Cam.Move(Ani->Cam.Right * sx + Ani->Cam.Up * sy);
        //}



        if (Ani->KeysClick['N'])
          glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else if (Ani->KeysClick['B'])
          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
        //if (Ani->KeysClick['P'])
        //  Ani->IsPause = !Ani->IsPause;

        /* Start of moving by axes if cases */
        
        if (Ani->Keys[VK_LSHIFT] && !Ani->Keys['S'])
        {

          Ani->Cam.Move(vec3(0, -10000 * Ani->GlobalDeltaTime, 0));
          RotXAngle = -10;

          if ((Ani->Cam.Loc[2] > 830 && Ani->Cam.Loc[2] < 840) || (Ani->Cam.Loc[2] > -605 && Ani->Cam.Loc[2] < -585))
          {
            if (Ani->Cam.Loc[0] < 11 && Ani->Cam.Loc[0] > -9)
              if (Ani->Cam.Loc[1] <= 7)
                Ani->Cam.Move(vec3(0, 10000 * Ani->GlobalDeltaTime, 0)), RotXAngle = 0;
          }
          else if (Ani->Cam.Loc[2] > -480 && Ani->Cam.Loc[2] < 490)
            if (Ani->Cam.Loc[0] < 370 && Ani->Cam.Loc[0] > -540)
              if (Ani->Cam.Loc[1] <= 7 && Ani->Cam.Loc[1] >= -5)
                Ani->Cam.Move(vec3(0, 10000 * Ani->GlobalDeltaTime, 0)), RotXAngle = 0;
        }
        else if (Ani->Keys[VK_SPACE] && !Ani->Keys['S'])
        {
          Ani->Cam.Move(vec3(0, 10000 * Ani->GlobalDeltaTime, 0)), RotXAngle = 20;
        }
        else
        {
          RotXAngle = 0;
        }

        
        //if (Ani->Keys[VK_SHIFT])
        //  Ani->Cam.Move(vec3(0, -100 * Ani->GlobalDeltaTime, 0));
        //else if (Ani->Keys[VK_SPACE])
        //  Ani->Cam.Move(vec3(0, 100 * Ani->GlobalDeltaTime, 0));
        /* End of moving by axes if cases */
        
        /* Moving by direction */
        if (Ani->Keys['W'])                                                                               //if (Ani->Keys['W'])
          Ani->Cam.Move(Dir * 11000 * Ani->GlobalDeltaTime * vec3(1, 0, 1));                                //  Ani->Cam.Move(Dir * Ani->GlobalDeltaTime * 300 * vec3(1, 0, 1));
        else if (Ani->Keys['S'])                                                                          //else if (Ani->Keys['S'])
          Ani->Cam.Move(Dir * -11000 * Ani->GlobalDeltaTime * vec3(1, 0, 1));                               //  Ani->Cam.Move(Dir * Ani->GlobalDeltaTime * -300 * vec3(1, 0, 1));
                                                                                                          //
        if (Ani->Keys['D'])                                                                               //if (Ani->Keys['D'])
        {
          Ani->Cam.Move(Right * 9000 * Ani->GlobalDeltaTime * vec3(1, 0, 1)), RotZAngle = -30;                              //  Ani->Cam.Move(Right * Ani->GlobalDeltaTime * 150 * vec3(1, 0, 1));
        }
        else if (Ani->Keys['A'])                                                                          //else if (Ani->Keys['A'])
        {
            Ani->Cam.Move(Right * -9000 * Ani->GlobalDeltaTime * vec3(1, 0, 1)), RotZAngle = 30;
            //  Ani->Cam.Move(Right * Ani->GlobalDeltaTime * -150 * vec3(1, 0, 1));
        }
        else
        {
          RotZAngle = 0;
        }

        /* End of moving by direction */
        
        /* Camera At rotate */
        //if (Ani->Keys['Q'] || Ani->Keys['E'])
        //{
        //  Ani->Cam.Rotate(vec3(0, 1, 0), (Ani->Keys['Q'] - Ani->Keys['E']) * 3000 * Ani->GlobalDeltaTime);
        //  //ARCRotate = ARCRotate * matr::Rotate((Ani->Keys['Q'] - Ani->Keys['E']) * 3000 * Ani->GlobalDeltaTime, Ani->Cam.Loc);
        //  RotYAngle += (Ani->Keys['Q'] - Ani->Keys['E']) * 0.005;
        //}
        //
        //if (Ani->Keys['Z'] || Ani->Keys['X'])
        //  Ani->Cam.Rotate(Right, (Ani->Keys['Z'] - Ani->Keys['X']) * 3000 * Ani->GlobalDeltaTime);

        //if (Ani->Keys['Z'] || Ani->Keys['X'])
        //{
        //  Ani->Cam.At = Ani->Cam.At + vec3(0, (-Ani->Keys['Z'] + Ani->Keys['X']) * 0.1, 0);
        //  Ani->Cam.SetLocAtUp(Ani->Cam.Loc, Ani->Cam.At, Up);
        //}
        /* End of camera At rotate if cases */
        
        //if (Ani->Keys[VK_LEFT] || Ani->Keys[VK_RIGHT])
        //{
        //  Ani->Cam.Loc = matr::RotateY((Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]) * Ani->GlobalDeltaTime * 30000).TransformPoint(Ani->Cam.Loc);
        //}
        //
        //if (Ani->Keys[VK_UP] || Ani->Keys[VK_DOWN])
        //{
        //  Ani->Cam.Loc = matr::RotateX((Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]) * Ani->GlobalDeltaTime * 30000).TransformPoint(Ani->Cam.Loc);
        //  
        //}


        Ani->Cam.SetLocAtUp(Ani->Cam.Loc, Ani->Cam.At, Ani->Cam.Up);
        Ani->Cam.SetRay(Ani->W / 2, Ani->H / 2);
        //ARCTranslate = ARCTranslate * matr::Translate(vec3(Ani->Cam.Loc[0], Ani->Cam.Loc[1], Ani->Cam.Loc[2]));
      }

      VOID Render( anim *Ani ) override
      {
        vec3 mov = Dir * 3 * vec3(1, 0, 1);
        vec3 Pos = vec3(Ani->Cam.Loc[0] + mov[0], Ani->Cam.Loc[1] - 1, Ani->Cam.Loc[2] + mov[2]);
        Ani->ModelDraw(&m3, matr::RotateX(RotXAngle) * matr::RotateZ(RotZAngle) * matr::Scale(0.0033) * matr::Translate(Pos));
      }

    };

    class pr : public unit
    {
    private:
      model mdl, mdl2, boss, pcf;
      BOOL pcfDrawFlag[3];
      vec3 PosPcf[3];
      BOOL BossDrawFlag;
      INT BossHitAmount;
      BOOL DrawFlag[7];
      BOOL DrawFlag2[7];
      vec3 Pos[7];
      vec3 Pos2[7];
      BOOL ResetFlag;
      BOOL AimFlag;
      sound s = sound("BIN/SOUNDS/laser.wav");
      sound s2 = sound("BIN/SOUNDS/say.wav");

    public:
      pr( VOID )
      {
        mdl.Load("BIN/MODELS/Fighter1.g3dm");
        mdl2.Load("BIN/MODELS/SPACE/ufo.g3dm");
        boss.Load("BIN/MODELS/SPACE/bb8.g3dm");
        pcf.Load("BIN/MODELS/rosaria.g3dm");
        for (INT i = 0; i < 7; i++)
          DrawFlag[i] = TRUE;
        for (INT i = 0; i < 7; i++)
          DrawFlag2[i] = TRUE;

        for (INT i = 0; i < 3; i++)
          pcfDrawFlag[i] = TRUE;
        BossDrawFlag = TRUE;
        BossHitAmount = 0;

        ResetFlag = FALSE;

        Pos[0] = vec3(50, 135, 435);
        Pos[1] = vec3(-300, 64, 420);
        Pos[2] = vec3(-100, 40, 50);
        Pos[3] = vec3(240, 110, -110);
        Pos[4] = vec3(-20, 86, -200);
        Pos[5] = vec3(20, 30, -450);
        Pos[6] = vec3(-13, 13, -560);

        Pos2[0] = vec3(-155, 120, 280);
        Pos2[1] = vec3(15, 75, 80);
        Pos2[2] = vec3(-60, 150, -95);
        Pos2[3] = vec3(-90, 80, 590);
        Pos2[4] = vec3(270, 35, 470);
        Pos2[5] = vec3(200, 11, 250);
        Pos2[6] = vec3(-30, 100, 40);


        PosPcf[0] = vec3(61, 63, -103);
        PosPcf[1] = vec3(50, 125, 380);
        PosPcf[2] = vec3(0, 5, -600);

        mdl.SetShader("ARC170");
        mdl2.SetShader("ARC170");
        boss.SetShader("ARC170");
        pcf.SetShader("ARC170");
        AimFlag = FALSE;
      }

      ~pr( VOID )
      {
      }

      VOID Response( anim *Ani ) override
      {
        SetCursorPos(Ani->W / 2, Ani->H / 2);

        if (Ani->KeysClick[VK_RETURN])
        {
          for (INT i = 0; i < 7; i++)
            if (Ani->Cam.Ray.SphereInter(Pos[i], 5))
              DrawFlag[i] = FALSE;
            else if (Ani->Cam.Ray.SphereInter(Pos2[i] + vec3(0, i * sin(Ani->Time) * 0.5, 0), 5))
              DrawFlag2[i] = FALSE;

          if (Ani->Cam.Ray.SphereInter(vec3(0, -140, 0), 100))
            BossHitAmount++;
          else if (Ani->Cam.Ray.SphereInter(vec3(61, 67, -103), 10))
            pcfDrawFlag[0] = FALSE, s2.Play();
          else if (Ani->Cam.Ray.SphereInter(vec3(50, 127, 380), 3))
            pcfDrawFlag[1] = FALSE, s2.Play();
          else if (Ani->Cam.Ray.SphereInter(vec3(0, 7, -600), 3))
            pcfDrawFlag[2] = FALSE, s2.Play();

          s.Play();
        }

        if (BossHitAmount >= 14)
          BossDrawFlag = FALSE;

        if (Ani->KeysClick['R'] || ResetFlag)
        {
          for (INT i = 0; i < 7; i++)
            DrawFlag[i] = TRUE, DrawFlag2[i] = TRUE;
          Ani->Cam.Loc = vec3(0, 7, 836);
          Ani->Cam.At = vec3(-3.3, 11, 0);
          BossDrawFlag = TRUE;
          BossHitAmount = 0;
          ResetFlag = FALSE;

          for (INT i = 0; i < 3; i++)
            pcfDrawFlag[i] = TRUE;

          s.Pause();
          s2.Pause();
        }

        if (Ani->KeysClick[VK_RCONTROL])
          AimFlag = !AimFlag;

        if (Ani->Cam.Loc[2] > -610 && Ani->Cam.Loc[2] < -590)
          if (Ani->Cam.Loc[0] > -15 && Ani->Cam.Loc[0] < 3)
            if (Ani->Cam.Loc[1] > 6.5 && Ani->Cam.Loc[1] < 7.1)
              ResetFlag = TRUE;

        if (AimFlag)
          Ani->Cam.SetProj(0.1, 0.2, 50000);
        else 
          Ani->Cam.SetProj(0.2, 0.1, 50000);
      }

      VOID Render( anim *Ani ) override
      {
        //Ani->PrimDraw(&cow, matr::Identity());
        for (INT i = 0; i < 7; i++)
          if (DrawFlag2[i])
            Ani->ModelDraw(&mdl2, matr::RotateZ(sin(Ani->Time) * 5) * matr::RotateY(Ani->Time * 20) * matr::Scale(vec3(0.01)) * matr::Translate(Pos2[i] + vec3(0, i * sin(Ani->Time) * 0.5, 0)));
        for (INT i = 0; i < 7; i++)
          if (DrawFlag[i])
            Ani->ModelDraw(&mdl, matr::RotateY(90) * matr::Scale(vec3(1)) * matr::Translate(Pos[i]));

        if (BossDrawFlag)
          Ani->ModelDraw(&boss, matr::RotateX(180) * matr::Scale(vec3(2)) * matr::Translate(vec3(0, -80, 0)));

        if (pcfDrawFlag[0])
          Ani->ModelDraw(&pcf, matr::Scale(vec3(0.003)) * matr::Translate(PosPcf[0]));
        if (pcfDrawFlag[1])
          Ani->ModelDraw(&pcf, matr::Scale(vec3(0.005)) * matr::Translate(PosPcf[1]));
        if (pcfDrawFlag[2])
          Ani->ModelDraw(&pcf, matr::Scale(vec3(0.005)) * matr::Translate(PosPcf[2]));
      }

    };

    class mod : public unit
    {
    private:
      model 
        m,
        m2,
        m4,
        //mb, 
        ml,
        m5;
    public:
      mod( VOID )
      {
        m.Load("BIN/MODELS/city_1.g3dm");
        m2.Load("BIN/MODELS/SPACE/Mars.g3dm");
        m4.Load("BIN/MODELS/SPACE/Station1.g3dm");
        m5.Load("BIN/MODELS/SPACE/IcelandicMountains.g3dm");
        //mb.Load("BIN/MODELS/SPACE/AU3DEADINSIDE.g3dm");
        ml.Load("BIN/MODELS/SPACE/can.g3dm");
        
        //mb.SetShader("CITY");
        ml.SetShader("CITY");
        m5.SetShader("ARC170");
        m.SetShader("CITY");
        //m4.SetShader("CITY");
      }

      ~mod( VOID )
      {
      }

      VOID Response( anim *Ani ) override
      {
      }

      VOID Render( anim *Ani ) override
      {
        //Ani->ModelDraw(&m, matr::Scale(0.01) * matr::RotateY(Ani->Time * 30));
        //Ani->ModelDraw(&m, matr::Scale(0.0001) * matr::Translate(vec3(1, 0, 0)));

        Ani->ModelDraw(&m, matr::Scale(30) * matr::Translate(vec3(0, 0, 100)));
        Ani->ModelDraw(&m2, matr::Scale(250));
        Ani->ModelDraw(&m5, matr::RotateX(180) * matr::Scale(vec3(17)) * matr::Translate(vec3(-100, -2.5, 0)));
        Ani->ModelDraw2(&m4, matr::Scale(0.1) * matr::Translate(vec3(0, 0, 830)));
        Ani->ModelDraw2(&m4, matr::Scale(0.1) * matr::Translate(vec3(-6, 0, -600)));
        //Ani->ModelDraw(&m4, matr::Scale(0.1) * matr::Translate(vec3(0, 0, 830)));
        //Ani->ModelDraw(&m4, matr::Scale(0.1) * matr::Translate(vec3(0, 0, -600)));

        //Ani->ModelDraw(&mb, matr::RotateX(-90) * matr::RotateY(Ani->Time * 20) * matr::RotateZ(sin(Ani->Time) * 10) * matr::Scale(vec3(1)) * matr::Translate(vec3(-100, -300, 550)));
        Ani->ModelDraw(&ml, matr::RotateY(Ani->Time * 20) * matr::RotateZ(sin(Ani->Time) * 10) * matr::Scale(vec3(150)) * matr::Translate(vec3(-10, -185, -35)));
      }
    };

    class music : public unit
    {
    public:
      sound s = sound("BIN/SOUNDS/eva.wav");

      music( VOID )
      {
        s.Play();
      }

      ~music( VOID )
      {

      }

      VOID Response( anim *Ani ) override
      {
        if (Ani->KeysClick['P'])
          s.Pause();
      }

      VOID Render( anim *Ani ) override
      {
      }
    };

  } /* End of 'units' namespace */
} /* End of 'nigl' namespace */

#endif /* __units_h_ */

/* END OF 'units.h' FILE */