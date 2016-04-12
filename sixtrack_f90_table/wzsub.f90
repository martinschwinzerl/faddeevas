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


