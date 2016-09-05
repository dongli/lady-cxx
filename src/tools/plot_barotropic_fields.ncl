load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_code.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_csm.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/contributed.ncl"

begin

  file_names = systemfunc("ls ./lady.fields.*.nc")

  num_time = dimsizes(file_names)-1

  wks = gsn_open_wks("pdf", "lady.fields")

  gsn_define_colormap(wks, "BlueRed")

  res0 = True
  res0@gsnDraw = False
  res0@gsnFrame = False
  ; res0@cnLinesOn = False
  ; res0@cnFillOn = True
  ; res0@cnFillMode = "RasterFill"
  ; res0@cnLevelSelectionMode = "ManualLevels"
  ; res0@cnMinLevelValF = 0.99
  ; res0@cnMaxLevelValF = 1.012
  ; res0@cnLevelSpacingF = 0.0005
  ; res0@cnMinLevelValF = -1.0e-4
  ; res0@cnMaxLevelValF = 1.0e-4
  ; res0@cnLevelSpacingF = 1.0e-5
  res0@trYMinF = 0.98
  res0@trYMaxF = 1.02

  res1 = True
  res1@gsnDraw = False
  res1@gsnFrame = False
  res1@trXMinF = 0
  res1@trXMaxF = num_time-1
  res1@trYMinF = 49000
  res1@trYMaxF = 49100
  res1@tiXAxisString = "Time step"
  res1@tiYAxisString = "Total energy"

  plot = new(2, graphic)

  total_energy = new(num_time, float)
  do ti = 0, num_time-1
    system("echo " + file_names(ti))
    f = addfile(file_names(ti), "r")
    ; plots(0) = gsn_csm_contour(wks, f->h(0,:,:), res)
    plot(0) = gsn_csm_xy(wks, f->x, f->h(0,10,:), res0)

    total_energy(ti) = f->total_energy(0)
    plot(1) = gsn_csm_xy(wks, ispan(0, ti, 1), total_energy(0:ti), res1)

    gsn_panel(wks, plot, (/2,1/), False)
  end do

end
