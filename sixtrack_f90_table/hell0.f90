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
      integer n,nc,nu
      double precision cc,h,one,q,rx,ry,saux,sx,sy,tn,two,tx,ty,wx,wy,x,&
     &xh,xl,xlim,xx,y,yh,ylim,yy
      parameter(cc = 1.12837916709551d0)
      parameter(one = 1.d0)
      parameter(two = 2.d0)
      parameter(xlim = 5.33d0)
      parameter(ylim = 4.29d0)
      dimension rx(33),ry(33)
!-----------------------------------------------------------------------
      x=abs(xx)
      y=abs(yy)
      if(y.lt.ylim.and.x.lt.xlim) then
        q=(one-y/ylim)*sqrt(one-(x/xlim)**2)
        h=one/(3.2d0*q)
!hr05   nc=7+int(23.0*q)
        nc=7+int(23.0d0*q)                                               !hr05
!       xl=h**(1-nc)
        xl=exp((1-nc)*log(h))                                            !yil11
        xh=y+0.5d0/h
        yh=x
        nu=10+int(21d0*q)

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
        wx=(two*exp(y**2-x**2))*cos((two*x)*y)-wx                        !hr05
        wy=((-1d0*two)*exp(y**2-x**2))*sin((two*x)*y)-wy                 !hr05
!hr05   if(xx.gt.0.) wy=-wy
        if(xx.gt.0.d0) wy=-1d0*wy                                        !hr05
      else
!hr05   if(xx.lt.0.) wy=-wy
        if(xx.lt.0.d0) wy=-1d0*wy
      endif
      end



      subroutine wzset
!  *********************************************************************
!------
!  This subroutine must be called before subroutine WZSUB can be used to
!  compute values of the complex error function w(z).
!------
!  Parameters xcut and ycut specify the opposite corners (xcut,0) and
!  (0,ycut) of the rectangle inside which interpolation is to be used
!  by subroutine WZSUB.
!------
!  Parameter h is the side of the squares of the interpolation grid.
!------
!  Parameters nx and ny must be set to the nearest integers to xcut/h
!  and ycut/h respectively (or to larger values).
!------
!  Calls MYWWERF new version of (CERN library) WWERF (C335)
!------
!  (G.A.Erskine, 29.09.1995)
!------
!  *********************************************************************
      implicit none
      integer i,j,k
      double precision wi,wr,x,y
      integer mbea,mcor,mcop,mmul,mpa,mran,nbb,nblo,nblz,ncom,ncor1,    &
     &nelb,nele,nema,ninv,nlya,nmac,nmon1,npart,nper,nplo,npos,nran,    &
     &nrco,ntr,nzfz
      parameter(npart = 64,nmac = 1)
      parameter(nele=1200,nblo=600,nper=16,nelb=140,nblz=20000,         &
     &nzfz = 300000,mmul = 20)
      parameter(nran = 2000000,ncom = 100,mran = 500,mpa = 6,nrco = 5,  &
     &nema = 15)
      parameter(mcor = 10,mcop = mcor+6, mbea = 99)
      parameter(npos = 20000,nlya = 10000,ninv = 1000,nplo = 20000)
      parameter(nmon1 = 600,ncor1 = 600)
      parameter(ntr = 20,nbb = 350)
      integer idim,kstep,nx,ny
      double precision h,half,hrecip,one,wtimag,wtreal,xcut,ycut
      parameter ( xcut = 7.77d0, ycut = 7.46d0 )
      parameter ( h = 1.d0/63.d0 )
      parameter ( nx = 490, ny = 470 )
      parameter ( idim = (nx+2)*(ny+2) )
      parameter ( half = 0.5d0, one = 1.d0 )
      common /wzcom1/ hrecip, kstep
      common /wzcom2/ wtreal(idim), wtimag(idim)
      save
!-----------------------------------------------------------------------
      hrecip = 1.d0/h
      kstep = nx+2
      k = 0
      do 2 j=0,ny+1
         do 1 i=0,nx+1
            k = k+1
!hr05       x=i*h
            x=dble(i)*h                                                  !hr05
!hr05       y=j*h
            y=dble(j)*h                                                  !hr05
            call mywwerf(x,y,wr,wi)
            wtreal(k)=wr
            wtimag(k)=wi
 1       continue
 2    continue
      end
      subroutine mywwerf(x,y,wr,wi)
      implicit none
      integer n
      double precision c,c1,c2,c3,c4,hf,p,rr,ri,sr0,sr,si,tr,ti,vi,vr,  &
     &wi,wr,x,xa,xl,y,ya,zhi,zhr,z1,z10
      parameter (z1=1,hf=z1/2d0,z10=10d0)
      parameter (c1=74d0/z10,c2=83d0/z10,c3=z10/32d0,c4=16d0/z10)
!     parameter (c=1.12837916709551257d0,p=(2d0*c4)**33)
      parameter (c=1.12837916709551257d0,p=46768052394588893.3825d0)
      dimension rr(37),ri(37)
      save
!-----------------------------------------------------------------------
      xa=abs(x)
      ya=abs(y)
      if(ya.lt.c1.and.xa.lt.c2) then
!        zh=dcmplx(ya+c4,xa)
        zhr=ya+c4
        zhi=xa
        rr(37)=0d0
        ri(37)=0d0
        do n=36,1,-1
!          t=zh+n*dconjg(r(n+1))
!hr05     tr=zhr+n*rr(n+1)
          tr=zhr+dble(n)*rr(n+1)                                         !hr05
!hr05     ti=zhi-n*ri(n+1)
          ti=zhi-dble(n)*ri(n+1)                                         !hr05
!          r(n)=hf*t/(dreal(t)**2+dimag(t)**2)
!hr05     rr(n)=hf*tr/(tr**2+ti**2)
          rr(n)=(hf*tr)/(tr**2+ti**2)                                    !hr05
!hr05     ri(n)=hf*ti/(tr**2+ti**2)
          ri(n)=(hf*ti)/(tr**2+ti**2)                                    !hr05
        enddo
        xl=p
        sr=0d0
        si=0d0
        do n=33,1,-1
          xl=c3*xl
!          s=r(n)*(s+xl)
          sr0=rr(n)*(sr+xl)-ri(n)*si
          si=rr(n)*si+ri(n)*(sr+xl)
          sr=sr0
        enddo
!        v=c*s
        vr=c*sr
        vi=c*si
      else
        zhr=ya
        zhi=xa
        rr(1)=0d0
        ri(1)=0d0
        do n=9,1,-1
!          t=zh+n*dconjg(r(1))
!hr05     tr=zhr+n*rr(1)
          tr=zhr+dble(n)*rr(1)                                           !hr05
!hr05     ti=zhi-n*ri(1)
          ti=zhi-dble(n)*ri(1)                                           !hr05
!          r(1)=hf*t/(dreal(t)**2+dimag(t)**2)
!hr05     rr(1)=hf*tr/(tr**2+ti**2)
          rr(1)=(hf*tr)/(tr**2+ti**2)                                    !hr05
!hr05     ri(1)=hf*ti/(tr**2+ti**2)
          ri(1)=(hf*ti)/(tr**2+ti**2)                                    !hr05
        enddo
!        v=c*r(1)
        vr=c*rr(1)
        vi=c*ri(1)
      endif
!hr05 if(ya.eq.0) then
      if(ya.eq.0d0) then                                                 !hr05
!        v=dcmplx(exp(-xa**2),dimag(v))
!hr05   vr=exp(-xa**2)
        vr=exp(-1d0*xa**2)                                            !hr05
      endif
      if(y.lt.0d0) then
!        v=2*exp(-dcmplx(xa,ya)**2)-v
!hr05   vr=2d0*exp(ya**2-xa**2)*cos(2d0*xa*ya)-vr
        vr=(2d0*exp(ya**2-xa**2))*cos((2d0*xa)*ya)-vr              !hr05
        vi=(-2d0*exp(ya**2-xa**2))*sin((2d0*xa)*ya)-vi             !hr05
!hr05   if(x.gt.0) vi=-vi
        if(x.gt.0d0) vi=-1d0*vi                                          !hr05
      else
!hr05   if(x.lt.0) vi=-vi
        if(x.lt.0d0) vi=-1d0*vi                                          !hr05
      endif
      wr=vr
      wi=vi
      return
      end

      subroutine wzsubv(n,vx,vy,vu,vv)
!  *********************************************************************
!------
!  This subroutine sets u=real(w(z)) and v=imag(w(z)), where z=x+i*y and
!  where w(z) is the complex error function defined by formula 7.1.3 in
!  "Handbook of Mathematical functions [eds. M.Abramowitz & I.A.Stegun,
!  Washington, 1966].  The absolute error of the computed value is less
!  than 1E-8.
!------
!  *** Note.  Subroutine WZSET must have been called before this sub-
!  routine can be used.
!------
!  For (x,y) inside the rectangle with opposite corners (xcut,0) and
!  (0,ycut), where xcut and ycut have been set by WZSET, an interpo-
!  lation formula is used.  For (x,y) outside this rectangle, a two-
!  term rational approximation is used.
!------
!  (G.A.Erskine, 29.09.1997)
!------
!  Vectorised for up to 64 argument values by E.McIntosh, 30.10.1997.
!  Much impoved using short vector buffers Eric 1st May, 2014.
!------
!  Third-order divided-difference interpolation over the corners of a
!  square [e.g. formula (2.5.1) in "Introduction to Numerical Analysis"
!  (F.B.Hildebrand New York, 1957), but with complex nodes and
!  function values].
!------
!  In the interpolation formula the corners of the grid square contain-
!  ing (x,y) are numbered (0,0)=3, (h,0)=4, (h,h)=1, (0,h)=2.
!  Identifiers d, dd and ddd denote divided-differences of orders 1, 2
!  and 3 respectively, and a preceding 't' indicates twice the value.
!------
!------
!  Two-term rational approximation to w(z) [Footnote to Table 7.9
!  in "Handbook of Mathematical Functions (eds. M.Abramowitz &
!  I.A.Stegun, Washington, 1966), but with additional digits in
!  the constants]:
!              u+i*v = i*z*( a1/(z**2-b1) + a2/(z**2-b2) ).
!  Maximum absolute error:
!        <1.E-6  for  x>=4.9  or  y>=4.4
!        <1.E-7  for  x>=6.1  or  y>=5.7
!        <1.E-8  for  x>=7.8  or  y>=7.5
!------
!  *********************************************************************
      implicit none
      dimension vx(*),vy(*),vu(*),vv(*)
      integer i,j,k,n,vmu,vnu
      double precision a1,a2,b1,b2,vd12i,vd12r,vd23i,vd23r,             &
     &vd34i,vd34r,vp,vq,vqsq,vr,vsimag,vsreal,vt,vtdd13i,vtdd13r,       &
     &vtdd24i,vtdd24r,vtdddi,vtdddr,vti,vtr,vu,vusum,vusum3,vv,         &
     &vvsum,vvsum3,vw1i,vw1r,vw2i,vw2r,vw3i,vw3r,vw4i,vw4r,vx,          &
     &vxh,vxhrel,vy,vyh,vyhrel
      integer npart
      parameter(npart = 64)
      integer idim,kstep,nx,ny
      double precision h,half,hrecip,one,wtimag,wtreal,xcut,ycut
      parameter ( xcut = 7.77d0, ycut = 7.46d0 )
      parameter ( h = 1.d0/63.d0 )
      parameter ( nx = 490, ny = 470 )
      parameter ( idim = (nx+2)*(ny+2) )
      parameter ( half = 0.5d0, one = 1.d0 )
      common /wzcom1/ hrecip, kstep
      common /wzcom2/ wtreal(idim), wtimag(idim)
      parameter ( a1 = 0.5124242248d0, a2 = 0.0517653588d0 )
      parameter ( b1 = 0.2752551286d0, b2 = 2.7247448714d0 )
      double precision xm,xx,yy
      parameter (xm=1d120)
!     temporary arrays to facilitate vectorisation
      integer in,out,ins,outs
      dimension ins(npart),outs(npart)
!-----------------------------------------------------------------------
      save
      in=0
      out=0
      do i=1,n
        if (vx(i).ge.xcut.or.vy(i).ge.ycut) then
          out=out+1
          outs(out)=i
          if (out.eq.npart) then
!     everything outside the rectangle so approximate
!     write (*,*) 'ALL outside'
!     write (*,*) 'i=',i
            do j=1,out
              xx=vx(outs(j))
              yy=vy(outs(j))
              if (xx.ge.xm) xx=xm
              if (yy.ge.xm) yy=xm
              vp=xx**2-yy**2
              vq=(2.d0*xx)*yy
              vqsq=vq**2
!  First term.
              vt=vp-b1
              vr=a1/(vt**2+vqsq)
              vsreal=vr*vt
              vsimag=-vr*vq
!  Second term
              vt=vp-b2
              vr=a2/(vt**2+vqsq)
              vsreal=vsreal+vr*vt
              vsimag=vsimag-vr*vq
!  Multiply by i*z.
              vu(outs(j))=-(yy*vsreal+xx*vsimag)
              vv(outs(j))=xx*vsreal-yy*vsimag
            enddo
            out=0
          endif
        else
          in=in+1
          ins(in)=i
          if (in.eq.npart) then
!     everything inside the square, so interpolate
!     write (*,*) 'ALL inside'
            do j=1,in
              vxh = hrecip*vx(ins(j))
              vyh = hrecip*vy(ins(j))
              vmu = int(vxh)
              vnu = int(vyh)
!  Compute divided differences.
              k = 2 + vmu + vnu*kstep
              vw4r = wtreal(k)
              vw4i = wtimag(k)
              k = k - 1
              vw3r = wtreal(k)
              vw3i = wtimag(k)
              vd34r = vw4r - vw3r
              vd34i = vw4i - vw3i
              k = k + kstep
              vw2r = wtreal(k)
              vw2i = wtimag(k)
              vd23r = vw2i - vw3i
              vd23i = vw3r - vw2r
              vtr = vd23r - vd34r
              vti = vd23i - vd34i
              vtdd24r = vti - vtr
!hr05 vtdd24i(j) = - ( vtr(j) + vti(j) )
              vtdd24i = -1d0* ( vtr + vti )                             !hr05
              k = k + 1
              vw1r = wtreal(k)
              vw1i = wtimag(k)
              vd12r = vw1r - vw2r
              vd12i = vw1i - vw2i
              vtr = vd12r - vd23r
              vti = vd12i - vd23i
              vtdd13r = vtr + vti
              vtdd13i = vti - vtr
              vtdddr = vtdd13i - vtdd24i
              vtdddi = vtdd24r - vtdd13r
!  Evaluate polynomial.
              vxhrel = vxh - dble(vmu)
              vyhrel = vyh - dble(vnu)
              vusum3=half*(vtdd13r+                                     &
     &       (vxhrel*vtdddr-vyhrel*vtdddi))
              vvsum3=half*(vtdd13i+                                     &
     &       (vxhrel*vtdddi+vyhrel*vtdddr))
              vyhrel = vyhrel - one
              vusum=vd12r+(vxhrel*vusum3-vyhrel*vvsum3)
              vvsum=vd12i+(vxhrel*vvsum3+vyhrel*vusum3)
              vxhrel = vxhrel - one
              vu(ins(j))=vw1r+(vxhrel*vusum-vyhrel*vvsum)
              vv(ins(j))=vw1i+(vxhrel*vvsum+vyhrel*vusum)
            enddo
            in=0
          endif
        endif
      enddo
!     everything outside the rectangle so approximate
!     write (*,*) 'ALL outside'
!     write (*,*) 'i=',i
      do j=1,out
        xx=vx(outs(j))
        yy=vy(outs(j))
        if (xx.ge.xm) xx=xm
        if (yy.ge.xm) yy=xm
        vp=xx**2-yy**2
        vq=(2.d0*xx)*yy
        vqsq=vq**2
!  First term.
        vt=vp-b1
        vr=a1/(vt**2+vqsq)
        vsreal=vr*vt
        vsimag=-vr*vq
!  Second term
        vt=vp-b2
        vr=a2/(vt**2+vqsq)
        vsreal=vsreal+vr*vt
        vsimag=vsimag-vr*vq
!  Multiply by i*z.
        vu(outs(j))=-(yy*vsreal+xx*vsimag)
        vv(outs(j))=xx*vsreal-yy*vsimag
      enddo
!     everything inside the square, so interpolate
!     write (*,*) 'ALL inside'
      do j=1,in
        vxh = hrecip*vx(ins(j))
        vyh = hrecip*vy(ins(j))
        vmu = int(vxh)
        vnu = int(vyh)
!  Compute divided differences.
        k = 2 + vmu + vnu*kstep
        vw4r = wtreal(k)
        vw4i = wtimag(k)
        k = k - 1
        vw3r = wtreal(k)
        vw3i = wtimag(k)
        vd34r = vw4r - vw3r
        vd34i = vw4i - vw3i
        k = k + kstep
        vw2r = wtreal(k)
        vw2i = wtimag(k)
        vd23r = vw2i - vw3i
        vd23i = vw3r - vw2r
        vtr = vd23r - vd34r
        vti = vd23i - vd34i
        vtdd24r = vti - vtr
!hr05 vtdd24i(j) = - ( vtr(j) + vti(j) )
        vtdd24i = -1d0* ( vtr + vti )                             !hr05
        k = k + 1
        vw1r = wtreal(k)
        vw1i = wtimag(k)
        vd12r = vw1r - vw2r
        vd12i = vw1i - vw2i
        vtr = vd12r - vd23r
        vti = vd12i - vd23i
        vtdd13r = vtr + vti
        vtdd13i = vti - vtr
        vtdddr = vtdd13i - vtdd24i
        vtdddi = vtdd24r - vtdd13r
!  Evaluate polynomial.
        vxhrel = vxh - dble(vmu)
        vyhrel = vyh - dble(vnu)
        vusum3=half*(vtdd13r+                                           &
     & (vxhrel*vtdddr-vyhrel*vtdddi))
        vvsum3=half*(vtdd13i+                                           &
     & (vxhrel*vtdddi+vyhrel*vtdddr))
        vyhrel = vyhrel - one
        vusum=vd12r+(vxhrel*vusum3-vyhrel*vvsum3)
        vvsum=vd12i+(vxhrel*vvsum3+vyhrel*vusum3)
        vxhrel = vxhrel - one
        vu(ins(j))=vw1r+(vxhrel*vusum-vyhrel*vvsum)
        vv(ins(j))=vw1i+(vxhrel*vvsum+vyhrel*vusum)
      enddo
      return
      end




      subroutine wzsub(x,y,u,v)
!  *********************************************************************
!
!  This subroutine sets u=real(w(z)) and v=imag(w(z)), where z=x+i*y and
!  where w(z) is the complex error function defined by formula 7.1.3 in
!  "Handbook of Mathematical functions [eds. M.Abramowitz & I.A.Stegun,
!  Washington, 1966].  The absolute error of the computed value is less
!  than 1E-8.
!
!  *** Note.  Subroutine WZSET must have been called before this sub-
!  routine can be used.
!
!  For (x,y) inside the rectangle with opposite corners (xcut,0) and
!  (0,ycut), where xcut and ycut have been set by WZSET, an interpo-
!  lation formula is used.  For (x,y) outside this rectangle, a two-
!  term rational approximation is used.
!
!  (G.A.Erskine, 29.09.1997)
!
!
!  Third-order divided-difference interpolation over the corners of a
!  square [e.g. formula (2.5.1) in "Introduction to Numerical Analysis"
!  (F.B.Hildebrand New York, 1957), but with complex nodes and
!  function values].
!
!  In the interpolation formula the corners of the grid square contain-
!  ing (x,y) are numbered (0,0)=3, (h,0)=4, (h,h)=1, (0,h)=2.
!  Identifiers d, dd and ddd denote divided-differences of orders 1, 2
!  and 3 respectively, and a preceding 't' indicates twice the value.
!
!  *********************************************************************
      implicit none
      integer k,mu,nu
      double precision a1,a2,b1,b2,d12i,d12r,d23i,d23r,d34i,d34r,p,     &
     &q,qsq,r,simag,sreal,t,tdd13i,tdd13r,tdd24i,tdd24r,tdddi,tdddr,ti, &
     &tr,u,usum,usum3,v,vsum,vsum3,w1i,w1r,w2i,w2r,w3i,w3r,w4i,w4r,x,xh,&
     &xhrel,y,yh,yhrel
      integer mbea,mcor,mcop,mmul,mpa,mran,nbb,nblo,nblz,ncom,ncor1,    &
     &nelb,nele,nema,ninv,nlya,nmac,nmon1,npart,nper,nplo,npos,nran,    &
     &nrco,ntr,nzfz
      parameter(npart = 64,nmac = 1)
      parameter(nele=1200,nblo=600,nper=16,nelb=140,nblz=20000,         &
     &nzfz = 300000,mmul = 20)
      parameter(nran = 2000000,ncom = 100,mran = 500,mpa = 6,nrco = 5,  &
     &nema = 15)
      parameter(mcor = 10,mcop = mcor+6, mbea = 99)
      parameter(npos = 20000,nlya = 10000,ninv = 1000,nplo = 20000)
      parameter(nmon1 = 600,ncor1 = 600)
      parameter(ntr = 20,nbb = 350)
      integer idim,kstep,nx,ny
      double precision h,half,hrecip,one,wtimag,wtreal,xcut,ycut
      parameter ( xcut = 7.77d0, ycut = 7.46d0 )
      parameter ( h = 1.d0/63.d0 )
      parameter ( nx = 490, ny = 470 )
      !parameter ( idim = (nx+2)*(ny+2) )
      parameter ( idim = 232224 )
      parameter ( half = 0.5d0, one = 1.d0 )
      common /wzcom1/ hrecip, kstep
      common /wzcom2/ wtreal(idim), wtimag(idim)
      parameter ( a1 = 0.5124242248d0, a2 = 0.0517653588d0 )
      parameter ( b1 = 0.2752551286d0, b2 = 2.7247448714d0 )

!-----------------------------------------------------------------------
      if ( x.ge.xcut .or. y.ge.ycut ) goto 1000
      xh = hrecip*x
      yh = hrecip*y
      mu = int(xh)
      nu = int(yh)
!  Compute divided differences.
      k = 2 + mu + nu*kstep
      w4r = wtreal(k)
      w4i = wtimag(k)
      k = k - 1
      w3r = wtreal(k)
      w3i = wtimag(k)
      d34r = w4r - w3r
      d34i = w4i - w3i
      k = k + kstep
      w2r = wtreal(k)
      w2i = wtimag(k)
      d23r = w2i - w3i
      d23i = w3r - w2r
      tr = d23r - d34r
      ti = d23i - d34i
      tdd24r = ti - tr
!hr05 tdd24i = - ( tr + ti )
      tdd24i = -1d0* ( tr + ti )                                         !hr05
      k = k + 1
      w1r = wtreal(k)
      w1i = wtimag(k)
      d12r = w1r - w2r
      d12i = w1i - w2i
      tr = d12r - d23r
      ti = d12i - d23i
      tdd13r = tr + ti
      tdd13i = ti - tr
      tdddr = tdd13i - tdd24i
      tdddi = tdd24r - tdd13r
!  Evaluate polynomial.
      xhrel = xh - dble(mu)
      yhrel = yh - dble(nu)
      usum3 = half*( tdd13r + ( xhrel*tdddr - yhrel*tdddi ) )
      vsum3 = half*( tdd13i + ( xhrel*tdddi + yhrel*tdddr ) )
      yhrel = yhrel - one
      usum = d12r + ( xhrel*usum3 - yhrel*vsum3 )
      vsum = d12i + ( xhrel*vsum3 + yhrel*usum3 )
      xhrel = xhrel - one
      u = w1r + ( xhrel*usum - yhrel*vsum )
      v = w1i + ( xhrel*vsum + yhrel*usum )
      return
!
!  Two-term rational approximation to w(z) [Footnote to Table 7.9
!  in "Handbook of Mathematical Functions (eds. M.Abramowitz &
!  I.A.Stegun, Washington, 1966), but with additional digits in
!  the constants]:
!              u+i*v = i*z*( a1/(z**2-b1) + a2/(z**2-b2) ).
!  Maximum absolute error:
!        <1.E-6  for  x>=4.9  or  y>=4.4
!        <1.E-7  for  x>=6.1  or  y>=5.7
!        <1.E-8  for  x>=7.8  or  y>=7.5
!
 1000 p=x**2-y**2
!hr05 q=2.d0*x*y
      q=(2.d0*x)*y                                                       !hr05
      qsq=q**2
!  First term.
      t=p-b1
      r=a1/(t**2+qsq)
      sreal=r*t
!hr05 simag=-r*q
      simag=(-1d0*r)*q                                                   !hr05
!  Second term
      t=p-b2
      r=a2/(t**2+qsq)
      sreal=sreal+r*t
      simag=simag-r*q
!  Multiply by i*z.
!hr05 u=-(y*sreal+x*simag)
      u=-1d0*(y*sreal+x*simag)                                           !hr05
      v=x*sreal-y*simag
      return
!
      end
 program hello
    double precision a,b,x,y,u,v
    integer i,j
    call wzset()
    x=1.0d0
    y=1.0d0
    do i=0,100
      do j=0,100
        a=16d0*i/100d0-8
        b=16d0*j/100d0-8
        x=10**a
        y=10**b
      call wzsub(x,y,u,v)
      write (*,"(6D40.30)") a,b,x,y,u,v
      enddo
    enddo
 end program hello

