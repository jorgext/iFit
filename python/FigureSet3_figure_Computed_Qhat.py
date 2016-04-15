#!/usr/bin/python
from numpy import loadtxt
from array import array
import sys, os, ROOT
factor = 1.

from AtlasStyle import SetAtlasStyle, AddLabel
SetAtlasStyle()

val1 = array("f",[0.005898617, 0.005165362, 0.004258343, 0.00296802])  
val2 = array("f",[0.010323031, 0.00856337,  0.006595172, 0.004195816])  
val3 = array("f",[0.012037537, 0.009770077, 0.007336914, 0.004535502])   
err1 = array("f",[0.004806898, 0.002295473, 0.002145582, 0.002349608]) 
err2 = array("f",[0.00841244,  0.003805538, 0.003323002, 0.003321582])
err3 = array("f",[0.009809625, 0.004341795, 0.003696731, 0.003590491]) 

xval = array("f",[0.32,0.53,0.75,0.94])
xerr = array("f",[0,0,0,0])
xval1 = array("f",[0,0,0,0])
xval2 = array("f",[0,0,0,0])
xval3 = array("f",[0,0,0,0])

offset = 0.0075
offset = 0.02
offset = offset/2
for i in range(4):   
  xval1[i] = xval[i] - offset
  xval2[i] = xval[i] 
  xval3[i] = xval[i] + offset 

g1 = ROOT.TGraphErrors(4,xval1,val1,xerr,err1)
g2 = ROOT.TGraphErrors(4,xval2,val2,xerr,err2)
g3 = ROOT.TGraphErrors(4,xval3,val3,xerr,err3)


# ROOT.gROOT.SetStyle("Plain")
# ROOT.gStyle.SetPadTickX(1)
# ROOT.gStyle.SetPadTickY(1)
# ROOT.gStyle.SetPadTopMargin(0.05)
# ROOT.gStyle.SetPadRightMargin(0.05)
# ROOT.gStyle.SetPadLeftMargin(0.125)
# ROOT.gStyle.SetPadBottomMargin(0.16)
# ROOT.gStyle.SetOptStat(0)
# ROOT.gStyle.SetOptTitle(0)
# ROOT.gStyle.SetEndErrorSize(7.5)

# Configuration
xlabel = "z_{h}"
# L_P configuration
ylabel = "#hat{q} [GeV^{2}/fm] "

fileout = "fig06a_qhat.pdf" #sys.argv[3]

ylo = 0
yhi = 0.024

markerSize = 2.0
lineWidth = 3
############# code
c = ROOT.TCanvas("canvas","canvas",800,600)
color = [1,2,4,8,9]
i = 0
g1.SetMarkerStyle(20+i)
g1.SetMarkerSize(markerSize)
g1.SetMarkerColor(color[i]) 
g1.SetLineColor(color[i])
# g1.SetLineWidth(lineWidth)
g1.GetXaxis().SetTitle(xlabel)
g1.GetYaxis().SetTitle(ylabel)
g1.GetYaxis().SetTitleOffset(1.75)
i = 1
g2.SetMarkerStyle(20+i)
g2.SetMarkerSize(markerSize)
g2.SetMarkerColor(color[i]) 
g2.SetLineColor(color[i])
# g2.SetLineWidth(lineWidth)
g2.GetXaxis().SetTitle(xlabel)
g2.GetYaxis().SetTitle(ylabel)
g2.GetYaxis().SetTitleOffset(1.75)
i = 2
g3.SetMarkerStyle(20+i)
g3.SetMarkerSize(markerSize)
g3.SetMarkerColor(color[i]) 
g3.SetLineColor(color[i])
# g3.SetLineWidth(lineWidth)
g3.GetXaxis().SetTitle(xlabel)
g3.GetYaxis().SetTitle(ylabel)
g3.GetYaxis().SetTitleOffset(1.75)

g1.GetYaxis().SetNdivisions(5+100*5);
g2.GetYaxis().SetNdivisions(5+100*5);


fontAxesSize = 28
fontAxesCode = 43
# axes range
g1.GetXaxis().SetRangeUser(0.01,0.99)
g1.GetYaxis().SetRangeUser(ylo,yhi)
g1.GetYaxis().SetTitleOffset(1.25)

x0 = 0.725
y0 = 0.725
x1 = x0 + 0.325
y1 = y0 + 0.17
leg = ROOT.TLegend(x0,y0,x1,y1)
leg.SetTextFont(43)
leg.SetTextSize(28)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
leg.SetHeader("  BLE40")
# leg.SetNColumns(3);
leg.AddEntry(g1,"Neon","ep")
leg.AddEntry(g2,"Krypton","ep")
leg.AddEntry(g3,"Xenon","ep")

g1.Draw("AP")
g2.Draw("P SAME")
g3.Draw("P SAME")
leg.Draw()
AddLabel(0.2,0.88,"#hat{q} = #Delta#LTp_{t}^{2}#GT/L_{p} with a 3 Parameter Fit")
AddLabel(0.2, 0.82, "Fixed cross section #sigma_{ph} = 40 [mbarn]")
c.Print(fileout)