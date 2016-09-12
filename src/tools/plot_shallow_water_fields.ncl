load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_code.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_csm.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/contributed.ncl"

begin

  file_names = systemfunc("ls ./lady.fields.*.nc")

  num_time = dimsizes(file_names)-1

  wks = gsn_open_wks("pdf", "lady.fields")

  cmap = (/(/1.0, 1.0, 1.0 /),(/0.0, 0.0, 0.0 /), \
           (/0.84,0.84,1.0 /),(/0.38,0.4, 0.98/), \
           (/0.04,0.15,0.89/),(/0.06,0.4, 0.46/), \
           (/0.15,0.71,0.14/),(/0.54,0.85,0.17/), \
           (/0.98,0.98,0.22/),(/0.99,0.53,0.14/), \
           (/0.99,0.09,0.11/)/)
  gsn_define_colormap(wks, cmap)

  res0 = True
  res0@gsnDraw = False
  res0@gsnFrame = False
  ; res0@cnLinesOn = False
  ; res0@cnFillOn = True
  ; res0@cnFillMode = "RasterFill"
  ; res0@cnLevelSelectionMode = "ManualLevels"
  ; res0@cnMinLevelValF = 1
  ; res0@cnMaxLevelValF = 1.001
  ; res0@cnLevelSpacingF = 0.0001
  ; res0@cnMinLevelValF = -1.0e-4
  ; res0@cnMaxLevelValF = 1.0e-4
  ; res0@cnLevelSpacingF = 1.0e-5
  res0@trYMinF = 0.98
  res0@trYMaxF = 1.02
  res0@tiYAxisString = "height (m)"

  res1 = True
  res1@gsnDraw = False
  res1@gsnFrame = False
  res1@trXMinF = 0
  res1@trXMaxF = num_time-1
  res1@trYMinF = 97000
  res1@trYMaxF = 99000
  res1@tiXAxisString = "Time step"
  res1@tiYAxisString = "Total energy"

  plot = new(2, graphic)

  total_energy = new(num_time, float)
  do ti = 0, num_time-1
    system("echo " + file_names(ti))
    f = addfile(file_names(ti), "r")
    printMinMax(f->h, 0)
    ; plot(0) = gsn_csm_contour(wks, f->h(0,:,:), res0)
    plot(0) = gsn_csm_xy(wks, f->x, f->h(0,10,:), res0)

    total_energy(ti) = f->total_energy(0)
    if (ti .le. 2) then
      plot(1) = gsn_csm_blank_plot(wks, res1)
    else
      plot(1) = gsn_csm_xy(wks, ispan(0, ti, 1), total_energy(0:ti), res1)
    end if

    gsn_panel(wks, plot, (/2,1/), False)
  end do

end
