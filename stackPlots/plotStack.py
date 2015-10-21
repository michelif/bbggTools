from pullClass import *
from ROOT import *
import json, os
import shutil

data_file = open("datasets.json")
data = json.load(data_file)

prefix = "PhoIDloose_"
dirSuffix = "25ns_150pb"
dirPrefix = "/afs/cern.ch/user/r/rateixei/www/HHBBGG/"
dirName = dirPrefix + dirSuffix

if not os.path.exists(dirName):
	print dirName, "doesn't exist, creating it..."
	os.makedirs(dirName)
	shutil.copy2(dirPrefix + "index.php", dirName+"/index.php")
	if os.path.exists(dirName):
		print dirName, "now exists!"


lumi = 150.0 #in pb

datasets = []

for bkg in data['background']:
	tempfile = TFile(bkg['file'])
	temptree = tempfile.Get('bbggSelectionTree')
	normalization = (lumi*bkg['xsec']*bkg['sfactor'])/(bkg['weight'])
	arr = [bkg['name'], bkg['legend'], bkg['file'], normalization, bkg['color']]
	dataset = [tempfile, temptree, arr]
	datasets.append(dataset)

print data['data']
f = TFile( data['data'] )
t = f.Get('bbggSelectionTree')

bhists = {}


Cut = " diphotonCandidate.M() > 80 "
Cut += " && dijetCandidate.M() > 80 "
Cut += " && leadingPhoton.pt() > 35 && subleadingPhoton.pt() > 35 "
Cut += " && leadingJet.pt() > 35 && subleadingJet.pt() > 35 "
#Cut += " && leadingJet.Eta() < 2. && leadingJet.Eta() > -2"
Cut += " && leadingPhotonID[0] == 1 "
Cut += " && subleadingPhotonID[0] == 1 "
#Cut += " && leadingPhotonEVeto == 0 "
#Cut += " && subleadingPhotonEVeto == 0 "
#Cut += " && leadingPhotonEVeto == 1 "
#Cut += " && subleadingPhotonEVeto == 1 "
#Cut += " && leadingPhotonISO[0] == 1 "
#Cut += " && subleadingPhotonISO[0] == 1 "
#Cut += " && leadingJet.pt() > 45 && subleadingJet.pt() > 45 "
#Cut += " && leadingJet_bDis > 0.9 && subleadingJet_bDis > 0.9"
weight = ""
weight += "( genTotalWeight )*"
#weight += "( genTotalWeight/fabs(genTotalWeight) )*"

cut = TCut(weight+"("+Cut+")")
cut_data = TCut(Cut)

#variable = "diHiggsCandidate.Pt()"
#varName = "DiHiggs Candidate p_{T} (GeV)"

plots = []

nbin = 50

plots.append(["diPho_Mass", "diphotonCandidate.M()", "DiPhoton Candidate Mass (GeV)", nbin, 80, 250])
plots.append(["diPho_Mass_HM", "diphotonCandidate.M()", "DiPhoton Candidate Mass (GeV)", nbin, 80, 2000])
plots.append(["diJet_Mass", "dijetCandidate.M()", "DiJet Candidate Mass (GeV)", nbin, 80, 500])
plots.append(["diJet_Mass_HM", "dijetCandidate.M()", "DiJet Candidate Mass (GeV)", nbin, 80, 2000])
plots.append(["leadingJet_pt", "leadingJet.pt()", "Leading Jet Pt (GeV)", nbin, 30, 400] )
plots.append(["leadingJet_eta", "leadingJet.Eta()", "Leading Jet Eta", nbin, -4, 4] )
plots.append(["leadingPhoton_eta", "leadingPhoton.Eta()", "Leading Photon Eta", nbin, -4, 4] )
plots.append(["dicandidate_Mass", "diHiggsCandidate.M()", "DiHiggs Candidate Mass (GeV)", nbin, 250, 1000])
plots.append(["dicandidate_Mass_HM", "diHiggsCandidate.M()", "DiHiggs Candidate Mass (GeV)", nbin, 250, 5000])
plots.append(["leadingPhoton_pt", "leadingPhoton.pt()", "Leading Photon Pt (GeV)", nbin, 30, 300])
plots.append(["btagSum", "leadingJet_bDis+subleadingJet_bDis", "Sum of b-tag of jet pair", nbin, 0, 2])
#plots[5] = ["dr_photons", "leadingPhoton.Dot(subleadingPhoton)", "Leading Photon Eta", 20, 0, 5] 

#variable = "diphotonCandidate.M()"
#varName = "DiPhoton Candidate Mass (GeV)"
for plot in plots:
	print plot
	h1 = TH1F("h1", "Histograms", plot[3], plot[4], plot[5])
	h1.Reset()
	variable = plot[1]
	varName = plot[2]
	stack = myStack('test'+plot[0], varName, varName, dirName, lumi)

	for bkg in datasets:
		print "Adding", bkg[0], 'to stack!'
	#	bfiles[bkg[0]] = TFile(bkg[2])
	#	btrees[bkg[0]] = bfiles[bkg[0]].Get('bbggSelectionTree')
		bhists[bkg[2][0]] = h1.Clone(bkg[2][0])
		bhists[bkg[2][0]].Reset()
		bkg[1].Draw(variable+'>>'+bkg[2][0], cut, 'hist')
		bhists[bkg[2][0]].Scale(bkg[2][3])
		bhists[bkg[2][0]].SetFillColor(bkg[2][4])
		bhists[bkg[2][0]].SetLineColor(bkg[2][4])
		bhists[bkg[2][0]].SetLineWidth(0)
		bhists[bkg[2][0]].SetFillStyle(3001)
		stack.addHist(bhists[bkg[2][0]], bkg[2][1], bkg[2][3])

	print 'Adding data to stack!'
	#h1.Reset()
#	f = TFile('data.root')
#	t = f.Get('bbggSelectionTree')
	data = h1.Clone("dat")
	data.Reset()
	t.Draw(variable+'>>dat', cut_data)
	data.SetMarkerStyle(8)
	data.Sumw2()
	data.SetMarkerColor(1)
	data.SetLineColor(1)
	data.SetLineWidth(3)
	stack.addData(data, "Data")

	stack.drawStack(prefix + plot[0])
#	stack.drawStack("DCM_" + plot[0])
	del stack
