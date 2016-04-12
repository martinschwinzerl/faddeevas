      subroutine errf(xx,yy,wx,wy)
!----------------------------------------------------------------------*
! purpose:                                                             *
!   modification of wwerf, double precision complex error function,    *
!   written at cern by k. koelbig.                                     *
!   taken from mad8                                                    *
! input:                                                               *
!   xx, yy    (real)    argument to cerf.                              *
! output:                                                              *
!   wx, wy    (real)    function result.                               *
!----------------------------------------------------------------------*
!---- double precision version.
      implicit none
+if cr
+ca crcoall
+ei
+if crlibm
+ca crlibco
+ei
      integer n,nc,nu
      double precision cc,h,one,q,rx,ry,saux,sx,sy,tn,two,tx,ty,wx,wy,x,&
     &xh,xl,xlim,xx,y,yh,ylim,yy
      parameter(cc = 1.12837916709551d0)
      parameter(one = 1.d0)
      parameter(two = 2.d0)
      parameter(xlim = 5.33d0)
      parameter(ylim = 4.29d0)
      dimension rx(33),ry(33)
+ca save
!-----------------------------------------------------------------------
      x=abs(xx)
      y=abs(yy)
      if(y.lt.ylim.and.x.lt.xlim) then
        q=(one-y/ylim)*sqrt(one-(x/xlim)**2)
        h=one/(3.2d0*q)
!hr05   nc=7+int(23.0*q)
        nc=7+int(23.0d0*q)                                               !hr05
!       xl=h**(1-nc)
+if crlibm
        xl=exp_rn((1-nc)*log_rn(h))                                      !yil11
+ei
+if .not.crlibm
        xl=exp((1-nc)*log(h))                                            !yil11
+ei
+if debug
!       call wda('errfq',q,nc,0,0,0)
!       call wda('errfh',h,nc,0,0,0)
!       call wda('errfxl',xl,nc,0,0,0)
+ei
+if debug
!       call wda('errfxlrn',xl,nc,0,0,0)
+ei
        xh=y+0.5d0/h
        yh=x
        nu=10+int(21d0*q)
+if debug
!       call wda('errfxh',xh,nu,0,0,0)
!       call wda('errfyh',yh,nu,0,0,0)
+ei
        rx(nu+1)=0d0
        ry(nu+1)=0d0
        do 10 n=nu,1,-1
!hr05     tx=xh+n*rx(n+1)
          tx=xh+dble(n)*rx(n+1)                                          !hr05
!hr05     ty=yh-n*ry(n+1)
          ty=yh-dble(n)*ry(n+1)                                          !hr05
!hr05     tn=tx*tx+ty*ty
          tn=tx**2+ty**2                                                 !hr05
!hr05     rx(n)=0.5d0*tx/tn
          rx(n)=(0.5d0*tx)/tn                                            !hr05
!hr05     ry(n)=0.5d0*ty/tn
          ry(n)=(0.5d0*ty)/tn                                            !hr05
   10   continue
        sx=0d0
        sy=0d0
        do 20 n=nc,1,-1
          saux=sx+xl
          sx=rx(n)*saux-ry(n)*sy
          sy=rx(n)*sy+ry(n)*saux
          xl=h*xl
   20   continue
        wx=cc*sx
        wy=cc*sy
      else
        xh=y
        yh=x
        rx(1)=0d0
        ry(1)=0d0
        do 30 n=9,1,-1
!hr05     tx=xh+n*rx(1)
          tx=xh+dble(n)*rx(1)                                            !hr05
!hr05     ty=yh-n*ry(1)
          ty=yh-dble(n)*ry(1)                                            !hr05
!hr05     tn=tx*tx+ty*ty
          tn=tx**2+ty**2                                                 !hr05
!hr05     rx(1)=0.5d0*tx/tn
          rx(1)=(0.5d0*tx)/tn                                            !hr05
!hr05     ry(1)=0.5d0*ty/tn
          ry(1)=(0.5d0*ty)/tn                                            !hr05
   30   continue
        wx=cc*rx(1)
        wy=cc*ry(1)
      endif
!      if(y.eq.0.) wx=exp(-x**2)
      if(yy.lt.0.d0) then
+if crlibm
!hr05   wx=two*exp_rn(y*y-x*x)*cos_rn(two*x*y)-wx
        wx=(two*exp_rn(y**2-x**2))*cos_rn((two*x)*y)-wx                  !hr05
+ei
+if .not.crlibm
!hr05   wx=two*exp(y*y-x*x)*cos(two*x*y)-wx
        wx=(two*exp(y**2-x**2))*cos((two*x)*y)-wx                        !hr05
+ei
+if crlibm
!hr05   wy=-two*exp_rn(y*y-x*x)*sin_rn(two*x*y)-wy
        wy=((-1d0*two)*exp_rn(y**2-x**2))*sin_rn((two*x)*y)-wy           !hr05
+ei
+if .not.crlibm
!hr05   wy=-two*exp(y*y-x*x)*sin(two*x*y)-wy
        wy=((-1d0*two)*exp(y**2-x**2))*sin((two*x)*y)-wy                 !hr05
+ei
!hr05   if(xx.gt.0.) wy=-wy
        if(xx.gt.0.d0) wy=-1d0*wy                                        !hr05
      else
!hr05   if(xx.lt.0.) wy=-wy
        if(xx.lt.0.d0) wy=-1d0*wy
      endif
      end
