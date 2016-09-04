load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_code.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_csm.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/contributed.ncl"

begin

  file_names = systemfunc("ls ./lady.quad_points.*.nc")

  wks = gsn_open_wks("pdf", "lady.quad_points")

  gsn_define_colormap(wks, "rainbow")
  colormap = gsn_retrieve_colormap(wks)

  rho_levels = fspan(1.0, 1.012, 51)
  u_levels = fspan(-0.01, 0.01, 21)
  v_levels = fspan(-0.01, 0.01, 21)

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

  do ti = 0, 0;dimsizes(file_names)-1
    system("echo " + file_names(ti))
    f = addfile(file_names(ti), "r")
    dims = dimsizes(f->x)
    num_parcel = dims(1)
    num_quad_point = dims(2)
    plot = gsn_csm_blank_plot(wks, res_bg)
    do pi = 0, num_parcel-1
      do qi = 0, num_quad_point-1
        res_point@gsMarkerColor = get_color_rgba(colormap, rho_levels, f->rho(0,pi,qi))
        gsn_polymarker(wks, plot, f->x(0,pi,qi,0), f->x(0,pi,qi,1), res_point)
      end do
    end do
    draw(plot)
    frame(wks)
    delete(f)
  end do

end
