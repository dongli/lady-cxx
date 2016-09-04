load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_code.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_csm.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/contributed.ncl"

begin

  file_names = systemfunc("ls ./lady.parcels.*.nc")

  follow_parcels = (/820,821,822,823,824/)

  wks = gsn_open_wks("pdf", "lady.parcels")

  res_bg = True
  res_bg@gsnDraw = False
  res_bg@gsnFrame = False
  res_bg@trXMinF = 0
  res_bg@trXMaxF = 100
  res_bg@trYMinF = 0
  res_bg@trYMaxF = 100

  res_point = True
  res_point@gsMarkerSizeF = 0.001
  res_point@gsMarkerIndex = 16

  res_shape = True
  res_shape@gsMarkerSizeF = 0.001
  res_shape@gsLineThicknessF = 0.01

  num_shape_point = 20
  x = new((/num_shape_point,2/), float)
  dtheta = 2 * atan(1.0) * 4 / (num_shape_point-1)
  do ti = 0, dimsizes(file_names)-1
    system("echo " + file_names(ti))
    f = addfile(file_names(ti), "r")
    dims = dimsizes(f->id)
    num_parcel = dims(1)
    plot = gsn_csm_blank_plot(wks, res_bg)
    do pi = 0, num_parcel-1
      gsn_polymarker(wks, plot, f->x(0,pi,0), f->x(0,pi,1), res_point)
      if (.not. any(follow_parcels .eq. pi)) then
        continue
      end if
      do si = 0, num_shape_point-1
        theta = dtheta * si
        y = (/cos(theta),sin(theta)/)
        x(si,:) = f->x(0,pi,:) + f->H(0,pi,:,:) # y
      end do
      gsn_polyline(wks, plot, x(:,0), x(:,1), res_shape)
    end do
    draw(plot)
    frame(wks)
    delete(plot)
    delete(f)
  end do

end
