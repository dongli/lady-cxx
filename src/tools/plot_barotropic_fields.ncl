load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_code.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_csm.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/contributed.ncl"

begin

  file_names = systemfunc("ls ./lady.fields.*.nc")

  wks = gsn_open_wks("pdf", "lady.fields")

  gsn_define_colormap(wks, "BlueRed")

  res = True
  res@cnLinesOn = False
  res@cnFillOn = True
  res@cnFillMode = "RasterFill"
  ; res@cnLevelSelectionMode = "ManualLevels"
  ; res@cnMinLevelValF = 0.99
  ; res@cnMaxLevelValF = 1.012
  ; res@cnLevelSpacingF = 0.0005
  ; res@cnMinLevelValF = -1.0e-4
  ; res@cnMaxLevelValF = 1.0e-4
  ; res@cnLevelSpacingF = 1.0e-5
  ; res@trYMinF = 0.98
  ; res@trYMaxF = 1.02

  do ti = 0, dimsizes(file_names)-1
    system("echo " + file_names(ti))
    f = addfile(file_names(ti), "r")
    plot = gsn_csm_contour(wks, f->v(0,:,:), res)
    ; plot = gsn_csm_xy(wks, f->x, f->h(0,10,:), res)
  end do

end
