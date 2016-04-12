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
      double precision sin_rn,cos_rn,tan_rn,sinh_rn,cosh_rn,asin_rn,    &
     &acos_rn,atan_rn,atan2_rn,exp_rn,log_rn,log10_rn
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
      double precision sin_rn,cos_rn,tan_rn,sinh_rn,cosh_rn,asin_rn,    &
     &acos_rn,atan_rn,atan2_rn,exp_rn,log_rn,log10_rn
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
!hr05   vr=exp_rn(-xa**2)
        vr=exp_rn(-1d0*xa**2)                                            !hr05
      endif
      if(y.lt.0d0) then
!        v=2*exp(-dcmplx(xa,ya)**2)-v
!hr05   vr=2d0*exp_rn(ya**2-xa**2)*cos_rn(2d0*xa*ya)-vr
        vr=(2d0*exp_rn(ya**2-xa**2))*cos_rn((2d0*xa)*ya)-vr              !hr05
        vi=(-2d0*exp_rn(ya**2-xa**2))*sin_rn((2d0*xa)*ya)-vi             !hr05
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


