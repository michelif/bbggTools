#include "flashgg/bbggTools/interface/bbggTools.h"
//FLASHgg files
#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "flashgg/DataFormats/interface/SinglePhotonView.h"
#include "flashgg/DataFormats/interface/Photon.h"
#include "flashgg/DataFormats/interface/Jet.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "TRandom.h"

using namespace std;

bool DEBUG = 0;

double mW = 80.3;
double mt = 173.5;

bool bbggTools::passHggPreselection(const flashgg::DiPhotonCandidate * dipho){

    bool isPreselected = false;

    if ( ( dipho->leadingPhoton()->full5x5_r9() > 0.8
           || dipho->leadingPhoton()->egChargedHadronIso() < 20
           || dipho->leadingPhoton()->egChargedHadronIso()/dipho->leadingPhoton()->pt() < 0.3 )
         &&
         ( dipho->subLeadingPhoton()->full5x5_r9() > 0.8
           || dipho->subLeadingPhoton()->egChargedHadronIso() < 20
           || dipho->subLeadingPhoton()->egChargedHadronIso()/dipho->subLeadingPhoton()->pt() < 0.3)
         && ( dipho->leadingPhoton()->hadronicOverEm() < 0.08 && dipho->subLeadingPhoton()->hadronicOverEm() < 0.08 )
         && ( dipho->leadingPhoton()->pt() > 30 && dipho->subLeadingPhoton()->pt() > 20)
         && ( fabs(dipho->leadingPhoton()->superCluster()->eta()) < 2.5 && fabs(dipho->subLeadingPhoton()->superCluster()->eta()) < 2.5 )
         && ( fabs(dipho->leadingPhoton()->superCluster()->eta()) < 1.4442 ||  fabs(dipho->leadingPhoton()->superCluster()->eta()) > 1.566 )
         && ( fabs(dipho->subLeadingPhoton()->superCluster()->eta()) < 1.4442 ||  fabs(dipho->subLeadingPhoton()->superCluster()->eta()) > 1.566 )
       ) {
	    isPreselected = true;
       }

    if (isPreselected) return true;
    else return false;
}

bool bbggTools::passHgg76XPreselection(const flashgg::DiPhotonCandidate * dipho, std::map<std::string, int> myTriggersResults){

    bool doTrig1 = false;
    bool doTrig2 = false;
    bool doTrig3 = false;

    if ( myTriggersResults["HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95_v"] == 1 )
      doTrig1 = true;
    else if ( myTriggersResults["HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55_v"] == 1 )
      doTrig2 = true;
    else if ( myTriggersResults["HLT_Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55_v"] == 1)
      doTrig3 = true;

    bool isPreselected_trig1 = false;
    bool isPreselected_trig2 = false;
    bool isPreselected_trig3 = false;


    //Trig1
    if ( doTrig1 )
      {
	if ( ( dipho->leadingPhoton()->full5x5_r9() > 0.8
	       || dipho->leadingPhoton()->egChargedHadronIso() < 20
	       || dipho->leadingPhoton()->egChargedHadronIso()/dipho->leadingPhoton()->pt() < 0.3)
	     &&
	     ( dipho->subLeadingPhoton()->full5x5_r9() > 0.8
	       || dipho->subLeadingPhoton()->egChargedHadronIso() < 20
	       || dipho->subLeadingPhoton()->egChargedHadronIso()/dipho->subLeadingPhoton()->pt() < 0.3)
	     &&	( dipho->leadingPhoton()->hadronicOverEm() < 0.08 && dipho->subLeadingPhoton()->hadronicOverEm() < 0.08 )
	     && ( dipho->leadingPhoton()->pt() > 30 && dipho->subLeadingPhoton()->pt() > 20)
	     &&	( fabs(dipho->leadingPhoton()->superCluster()->eta()) < 2.5 && fabs(dipho->subLeadingPhoton()->superCluster()->eta()) < 2.5 )
	     &&	( fabs(dipho->leadingPhoton()->superCluster()->eta()) < 1.4442 ||  fabs(dipho->leadingPhoton()->superCluster()->eta()) > 1.566 )
	     &&	( fabs(dipho->subLeadingPhoton()->superCluster()->eta()) < 1.4442 ||  fabs(dipho->subLeadingPhoton()->superCluster()->eta()) > 1.566 )
	     )
	  {
	    isPreselected_trig1 = true;
	  }
      }


    //Trig2
    if ( doTrig2 )
      {
	if ( ( dipho->leadingPhoton()->full5x5_r9() > 0.8 && dipho->subLeadingPhoton()->full5x5_r9() > 0.8)
	     && ( dipho->leadingPhoton()->egChargedHadronIso() < 20 || dipho->leadingPhoton()->egChargedHadronIso()/dipho->leadingPhoton()->pt() < 0.3)
	     && ( dipho->subLeadingPhoton()->egChargedHadronIso() < 20 || dipho->subLeadingPhoton()->egChargedHadronIso()/dipho->subLeadingPhoton()->pt() < 0.3)
	     && ( dipho->leadingPhoton()->hadronicOverEm() < 0.08 && dipho->subLeadingPhoton()->hadronicOverEm() < 0.08 )
	     && ( dipho->leadingPhoton()->hasPixelSeed() == 0 && dipho->subLeadingPhoton()->hasPixelSeed() == 0)
	     && ( dipho->leadingPhoton()->pt() > 30 && dipho->subLeadingPhoton()->pt() > 20)
	     && ( fabs(dipho->leadingPhoton()->superCluster()->eta()) < 2.5 && fabs(dipho->subLeadingPhoton()->superCluster()->eta()) < 2.5 )
	     && ( fabs(dipho->leadingPhoton()->superCluster()->eta()) < 1.4442 ||  fabs(dipho->leadingPhoton()->superCluster()->eta()) > 1.566 )
	     && ( fabs(dipho->subLeadingPhoton()->superCluster()->eta()) < 1.4442 ||  fabs(dipho->subLeadingPhoton()->superCluster()->eta()) > 1.566 )
	     )
	  {
	    isPreselected_trig2 = true;
	  }
      }

    if ( doTrig3 )
      {
	if ( ( dipho->leadingPhoton()->full5x5_r9() > 0.8
	       || dipho->leadingPhoton()->egChargedHadronIso() < 20
	       || dipho->leadingPhoton()->egChargedHadronIso()/dipho->leadingPhoton()->pt() < 0.3)
	     &&
	     ( dipho->subLeadingPhoton()->full5x5_r9() > 0.8
	       || dipho->subLeadingPhoton()->egChargedHadronIso() < 20
	       || dipho->subLeadingPhoton()->egChargedHadronIso()/dipho->subLeadingPhoton()->pt() < 0.3 )
	     && ( dipho->leadingPhoton()->hadronicOverEm() < 0.08 && dipho->subLeadingPhoton()->hadronicOverEm() < 0.08 )
	     && ( dipho->leadingPhoton()->pt() > 30 && dipho->subLeadingPhoton()->pt() > 20)
	     && ( fabs(dipho->leadingPhoton()->superCluster()->eta()) < 1.442 && fabs(dipho->subLeadingPhoton()->superCluster()->eta()) < 1.442 )
	     && ( dipho->leadingPhoton()->hasPixelSeed() == 0 && dipho->subLeadingPhoton()->hasPixelSeed() == 0)
	     )
	  {
	    isPreselected_trig3 = true;
	  }
      }

    if (isPreselected_trig1 || isPreselected_trig2 || isPreselected_trig3) return true;
    else return false;

}


std::vector<flashgg::DiPhotonCandidate> bbggTools::DiPhotonPreselectionTnP2016(vector<flashgg::DiPhotonCandidate> diphoCol, std::map<std::string, int> myTriggersResults)
{
  std::vector<flashgg::DiPhotonCandidate> selDiPhos;

  for ( unsigned int dp = 0; dp < diphoCol.size(); dp++)
    {
      flashgg::DiPhotonCandidate dipho = diphoCol[dp];

      if (passPreselectionTnP2016(&dipho, myTriggersResults)){
	selDiPhos.push_back(dipho);
	continue;
      }

    }

  return selDiPhos;
}


bool bbggTools::passPreselectionTnP2016(const flashgg::DiPhotonCandidate * dipho, std::map<std::string, int> myTriggersResults){

  bool isPreselected = false;
  //this should not be needed since photons are preselected, but just be sure

  if ( myTriggersResults["HLT_Ele27_WPTight_Gsf_v"] != 1 )
    return false;


  if ( ( dipho->leadingPhoton()->full5x5_r9() > 0.8
	 || dipho->leadingPhoton()->egChargedHadronIso() < 20
	 || dipho->leadingPhoton()->egChargedHadronIso()/dipho->leadingPhoton()->pt() < 0.3 )
         &&
       ( dipho->subLeadingPhoton()->full5x5_r9() > 0.8
	 || dipho->subLeadingPhoton()->egChargedHadronIso() < 20
	 || dipho->subLeadingPhoton()->egChargedHadronIso()/dipho->subLeadingPhoton()->pt() < 0.3)
       && ( dipho->leadingPhoton()->hadronicOverEm() < 0.08 && dipho->subLeadingPhoton()->hadronicOverEm() < 0.08 )
       && ( dipho->leadingPhoton()->pt() > 30 && dipho->subLeadingPhoton()->pt() > 20)
       && ( fabs(dipho->leadingPhoton()->superCluster()->eta()) < 2.5 && fabs(dipho->subLeadingPhoton()->superCluster()->eta()) < 2.5 )
       && ( fabs(dipho->leadingPhoton()->superCluster()->eta()) < 1.4442 ||  fabs(dipho->leadingPhoton()->superCluster()->eta()) > 1.566 )
       && ( fabs(dipho->subLeadingPhoton()->superCluster()->eta()) < 1.4442 ||  fabs(dipho->subLeadingPhoton()->superCluster()->eta()) > 1.566 )
       ) {
    isPreselected = true;
  }

  if (isPreselected) return true;
  else return false;


}


std::vector<flashgg::DiPhotonCandidate> bbggTools::DiPhoton76XPreselection(vector<flashgg::DiPhotonCandidate> diphoCol, std::map<std::string, int> myTriggersResults)
{
    std::vector<flashgg::DiPhotonCandidate> selDiPhos;

    for ( unsigned int dp = 0; dp < diphoCol.size(); dp++)
    {
      flashgg::DiPhotonCandidate dipho = diphoCol[dp];

      if (passHgg76XPreselection(&dipho, myTriggersResults)){
	selDiPhos.push_back(dipho);
	continue;
      }

    }

    return selDiPhos;
}

std::vector<flashgg::DiPhotonCandidate> bbggTools::DiPhotonPreselection(vector<flashgg::DiPhotonCandidate> diphoCol)
{
    std::vector<flashgg::DiPhotonCandidate> selDiPhos;

    for ( unsigned int dp = 0; dp < diphoCol.size(); dp++)
    {
      flashgg::DiPhotonCandidate dipho = diphoCol[dp];

      if (passHggPreselection(&dipho)){
	selDiPhos.push_back(dipho);
	continue;
      }
    }

    return selDiPhos;
}

std::map<std::string,int> bbggTools::TriggerSelection(std::vector<std::string> myTriggers, const edm::TriggerNames &names, edm::Handle<edm::TriggerResults> triggerBits)
{
    std::map<std::string,int> triggerResults;
    for(unsigned int j = 0; j < myTriggers.size(); j++)
    {
        int accepted = 0;
        for ( unsigned int i = 0; i < triggerBits->size(); i++)
        {
	  //            if(DEBUG) std::cout << "[bbggTools::TriggerSelection] Trigger name: " << names.triggerName(i) << " \t Decision: " << triggerBits->accept(i) << std::endl;
            if((names.triggerName(i)).find(myTriggers[j]) != std::string::npos )
            {
                if(triggerBits->accept(i) == 1){
                    accepted = 1;
                }
            }
        }
//        triggerResults.push_back(accepted);
        triggerResults[myTriggers[j]] = accepted;
    }
    return triggerResults;
}

std::vector<float> bbggTools::CosThetaAngles(const flashgg::DiPhotonCandidate* DiPhoton, flashgg::Jet LeadingJet, flashgg::Jet SubleadingJet)
{

    bbggTools::LorentzVector diJetCandidate = LeadingJet.p4() + SubleadingJet.p4();
    bbggTools::LorentzVector diHiggsCandidate = DiPhoton->p4() + diJetCandidate;

    std::vector<float> helicityThetas;

    TLorentzVector BoostedHgg(0,0,0,0);
    BoostedHgg.SetPtEtaPhiE( DiPhoton->pt(), DiPhoton->eta(), DiPhoton->phi(), DiPhoton->energy());
    TLorentzVector HHforBoost(0,0,0,0);
    HHforBoost.SetPtEtaPhiE( diHiggsCandidate.pt(), diHiggsCandidate.eta(), diHiggsCandidate.phi(), diHiggsCandidate.energy());
    helicityThetas.push_back( bbggTools::HelicityCosTheta(HHforBoost, BoostedHgg));

    TLorentzVector BoostedLeadingJet(0,0,0,0);
    BoostedLeadingJet.SetPtEtaPhiE( LeadingJet.pt(), LeadingJet.eta(), LeadingJet.phi(), LeadingJet.energy());
    TLorentzVector HbbforBoost(0,0,0,0);
    HbbforBoost.SetPtEtaPhiE( diJetCandidate.pt(), diJetCandidate.eta(), diJetCandidate.phi(), diJetCandidate.energy());
    helicityThetas.push_back( bbggTools::HelicityCosTheta(HbbforBoost, BoostedLeadingJet));
    
    TLorentzVector BoostedLeadingPhoton(0,0,0,0);
    BoostedLeadingPhoton.SetPtEtaPhiE( DiPhoton->leadingPhoton()->pt(), DiPhoton->leadingPhoton()->eta(), DiPhoton->leadingPhoton()->phi(), DiPhoton->leadingPhoton()->energy());
    helicityThetas.push_back( bbggTools::HelicityCosTheta(BoostedHgg, BoostedLeadingPhoton));

    helicityThetas.push_back( bbggTools::HelicityCosTheta(BoostedHgg, HbbforBoost));
    helicityThetas.push_back( bbggTools::HelicityCosTheta(HbbforBoost, BoostedHgg));

    return helicityThetas;

}

float bbggTools::HelicityCosTheta( TLorentzVector Booster, TLorentzVector Boosted)
{
    TVector3 BoostVector = Booster.BoostVector();
    Boosted.Boost( -BoostVector.x(), -BoostVector.y(), -BoostVector.z() );
    return Boosted.CosTheta();
}

std::vector<TVector3> bbggTools::norm_planes_hi(std::vector<TLorentzVector> partons, TLorentzVector dihiggs)
{
  TVector3 boost_H = -dihiggs.BoostVector();

  std::vector<TVector3> partons3v(4);

  for (int i = 0; i < 4; i++){
    partons[i].Boost(boost_H);
    partons3v[i] = partons[i].Vect().Unit();
  }

  vector<TVector3> vnorm(2);

  TRandom R;

  for (int i = 0; i < 2; i++){
    double rndm = R.Uniform(1);
    if (rndm > 0.5) vnorm[i] = (partons3v[i*2].Cross(partons3v[i*2+1])).Unit();
    else vnorm[i] = -1*(partons3v[i*2].Cross(partons3v[i*2+1])).Unit();
  }

   
  return vnorm;

}

std::vector<double> bbggTools::getPhi(const flashgg::DiPhotonCandidate * DiPhoton, flashgg::Jet LeadingJet, flashgg::Jet SubleadingJet)
{

  TLorentzVector leadingPhoton, subleadingPhoton, leadingJet, subleadingJet, diphoton, dihiggs;
  leadingPhoton.SetPtEtaPhiE(DiPhoton->leadingPhoton()->pt(), DiPhoton->leadingPhoton()->eta(), DiPhoton->leadingPhoton()->phi(), DiPhoton->leadingPhoton()->energy());
  subleadingPhoton.SetPtEtaPhiE(DiPhoton->subLeadingPhoton()->pt(), DiPhoton->subLeadingPhoton()->eta(), DiPhoton->subLeadingPhoton()->phi(), DiPhoton->subLeadingPhoton()->energy());
  leadingJet.SetPtEtaPhiE( LeadingJet.pt(), LeadingJet.eta(), LeadingJet.phi(), LeadingJet.energy());
  subleadingJet.SetPtEtaPhiE( SubleadingJet.pt(), SubleadingJet.eta(), SubleadingJet.phi(), SubleadingJet.energy());
  diphoton = leadingPhoton + subleadingPhoton;
  dihiggs = diphoton + leadingJet + subleadingJet;

  vector<double> vPhi(2);
  vector<TLorentzVector> partons(4);
  partons[0] = leadingPhoton;
  partons[1] = subleadingPhoton;
  partons[2] = leadingJet;
  partons[3] = subleadingJet; 

  // Define hgg direction
  TLorentzVector hgg = diphoton;
  TVector3 boost_H = - dihiggs.BoostVector();
  hgg.Boost(boost_H);
  TVector3 hgg_vect = diphoton.Vect().Unit();

  // Calculate the normal to Hgg and hbbdecay plane
  vector<TVector3> vnorm = bbggTools::norm_planes_hi(partons, dihiggs);


  // ====================================================================

  // Calculate Phi
  double dsignhgg = hgg_vect.Dot(vnorm[1].Cross(vnorm[0]))/(abs(hgg_vect.Dot(vnorm[1].Cross(vnorm[0]))));
  vPhi[0] = dsignhgg*(-1)*acos(vnorm[0].Dot(vnorm[1]));

  // ==========================

  // Define z direction
  TLorentzVector p1(0, 0,  6500, 6500);
  TVector3 z_vect = p1.Vect().Unit();

  // Calcuate the normal Hgg and Hbb 
  TVector3 zzprime = (z_vect.Cross(hgg_vect)).Unit();

  // Calculate Phi1
  dsignhgg = hgg_vect.Dot(zzprime.Cross(vnorm[0]))/(fabs(hgg_vect.Dot(zzprime.Cross(vnorm[0]))));
  vPhi[1] = dsignhgg*acos(zzprime.Dot(vnorm[0]));

  return vPhi;
}

float bbggTools::getCosThetaStar_CS(TLorentzVector h1, TLorentzVector h2, float ebeam) {
  // cos theta star angle in the Collins Soper frame
  // Copied directly from here: https://github.com/ResonantHbbHgg/Selection/blob/master/selection.h#L3367-L3385
  TLorentzVector p1, p2;
  p1.SetPxPyPzE(0, 0,  ebeam, ebeam);
  p2.SetPxPyPzE(0, 0, -ebeam, ebeam);

  TLorentzVector hh;
  hh = h1 + h2;

  TVector3 boost = - hh.BoostVector();
  p1.Boost(boost);
  p2.Boost(boost);
  h1.Boost(boost);

  TVector3 CSaxis = p1.Vect().Unit() - p2.Vect().Unit();
  CSaxis.Unit();

  return cos(   CSaxis.Angle( h1.Vect().Unit() )    );
}


bool bbggTools::isJetID(edm::Ptr<flashgg::Jet> jet, bool useTight)
{
  return bbggTools::isJetID(jet.get(), useTight);
}

bool bbggTools::isJetID(const flashgg::Jet *jet, bool useTight)
{
  double NHF  = jet->neutralHadronEnergyFraction();
  double NEMF = jet->neutralEmEnergyFraction();
  double NumConst = jet->chargedMultiplicity()+jet->neutralMultiplicity();
  double CHF  = jet->chargedHadronEnergyFraction();
  double CHM  = jet->chargedMultiplicity();
  double CEMF = jet->chargedEmEnergyFraction();
  double NNP  = jet->neutralMultiplicity();

  double jetEta = jet->eta();
  bool looseJetID = false;
  bool tightJetID = false;

  if (fabs(jetEta) <= 2.7){
    looseJetID = (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((fabs(jetEta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || fabs(jetEta)>2.4);
    tightJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1) && ((fabs(jetEta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || fabs(jetEta)>2.4);
  }
  else if ( fabs(jetEta) <= 3.0){
    looseJetID = (NEMF<0.90 && NNP>2);
    tightJetID = (NEMF<0.90 && NNP>2);
  }
  else{
    looseJetID = (NEMF<0.90 && NNP>10); 
    tightJetID = (NEMF<0.90 && NNP>10);
  }

  if (useTight) return tightJetID;
  else return looseJetID;
}


std::map<int, vector<double> > bbggTools::getWhichID (std::string wpoint)
{
    if( wpoint.find("loose") != std::string::npos) {
        return _phoIDloose;
    }
    if( wpoint.find("medium") != std::string::npos) {
        return _phoIDmedium;
    }
    if( wpoint.find("tight") != std::string::npos) {
        return _phoIDtight;
    }
    std::cout << "[bbggTools::getWhichID] " << wpoint << " has to be either loose, medium or tight!" << std::endl;
    std::map<int, vector<double> > empty;
    return empty;
}
std::map<int, vector<double> > bbggTools::getWhichISO (std::string wpoint)
{
    if( wpoint.find("loose") != std::string::npos) {
        return _phoISOloose;
    }
    if( wpoint.find("medium") != std::string::npos) {
        return _phoISOmedium;
    }
    if( wpoint.find("tight") != std::string::npos) {
        return _phoISOtight;
    }
    std::cout << "[bbggTools::getWhichISO] " << wpoint << " has to be either loose, medium or tight!" << std::endl;
    std::map<int, vector<double> > empty;
    return empty;
}

double bbggTools::getCHisoToCutValue(edm::Ptr<flashgg::DiPhotonCandidate> dipho, int whichPho)
{
    return bbggTools::getCHisoToCutValue(dipho.get(), whichPho);
}

double bbggTools::getCHisoToCutValue(const flashgg::DiPhotonCandidate * dipho, int whichPho)
{
	if(rho_ == -10 ){
		cout << "[bbggTools::getCHisoToCutValue] You have to do tools->setRho(rho)!" << endl;
		return -1;
	}
	if( whichPho > 1 ) {
		std::cout << "[bbggTools::getCHisoToCutValue] You chose the wrong photon!" << std::endl;
		return -1;
	}
	double PFIso = -1, eta = -99;
	if(whichPho == 0) {
		PFIso = dipho->leadingView()->pfChIso03WrtChosenVtx();
		eta = dipho->leadingPhoton()->superCluster()->eta();
	}
	if(whichPho == 1) {
		PFIso = dipho->subLeadingView()->pfChIso03WrtChosenVtx();
		eta = dipho->subLeadingPhoton()->superCluster()->eta();
	}

	double EA = bbggTools::getEA(eta, 0);
	double finalValue = fmax(PFIso - rho_*EA, 0.);
	return finalValue;
}

double bbggTools::getNHisoToCutValue(const flashgg::Photon* pho, vector<double> nhCorr)
{
	if(rho_ == -10 ){
		cout << "[bbggTools::getNHisoToCutValue] You have to do tools->setRho(rho)!" << endl;
		return -1;
	}
	if( nhCorr.size() < 2 ) {
		cout << "[bbggTools::getNHisoToCutValue] nhCorr vector not initialized correctly!" << endl;
		return -1;
	}
	double PFIso = pho->pfNeutIso03();
	double eta = pho->superCluster()->eta();
	double EA = bbggTools::getEA(eta, 1);
//	double extraFactor = exp(nhCorr[0]*pho->pt()+nhCorr[1]);
	double extraFactor = nhCorr[0]*pho->pt()+nhCorr[1]*(pho->pt())*(pho->pt());
	double finalValue = fmax(PFIso - rho_*EA, 0.) - extraFactor;
	return finalValue;
}

double bbggTools::getPHisoToCutValue(const flashgg::Photon* pho, vector<double> phCorr)
{
	if(rho_ == -10 ){
		cout << "[bbggTools::getPHisoToCutValue] You have to do tools->setRho(rho)!" << endl;
		return -1;
	}
	if( phCorr.size() < 2 ) {
		cout << "[bbggTools::getPHisoToCutValue] phCorr vector not initialized correctly!" << endl;
		return -1;
	}
	double PFIso = pho->pfPhoIso03();
	double eta = pho->superCluster()->eta();
	double EA = bbggTools::getEA(eta, 2);
	double extraFactor = phCorr[0]*pho->pt() + phCorr[1];
	double finalValue = fmax(PFIso - rho_*EA, 0.) - extraFactor;
	return finalValue;
}

double bbggTools::getEA( float eta, int whichEA){
        if(whichEA < 0 || whichEA > 2){
                std::cout << "WRONG EA TYPE" << std::endl;
                return -1;
        }

        float EA[7][3];

        //Spring 15 25ns values ("Please note that the Charged Hadron Isolation is NOT corrected with Effective Areas in the SP15 25ns ID")
        EA[0][0] = 0.0; EA[0][1] = 0.0599; EA[0][2] = 0.1271;
        EA[1][0] = 0.0; EA[1][1] = 0.0819; EA[1][2] = 0.1101;
        EA[2][0] = 0.0; EA[2][1] = 0.0696; EA[2][2] = 0.0756;
        EA[3][0] = 0.0; EA[3][1] = 0.0360; EA[3][2] = 0.1175;
        EA[4][0] = 0.0; EA[4][1] = 0.0360; EA[4][2] = 0.1498;
        EA[5][0] = 0.0; EA[5][1] = 0.0462; EA[5][2] = 0.1857;
        EA[6][0] = 0.0; EA[6][1] = 0.0656; EA[6][2] = 0.2183;

        float feta = fabs(eta);

        if(feta > 0.000 && feta < 1.000 ) return EA[0][whichEA];
        if(feta > 1.000 && feta < 1.479 ) return EA[1][whichEA];
        if(feta > 1.479 && feta < 2.000 ) return EA[2][whichEA];
        if(feta > 2.000 && feta < 2.200 ) return EA[3][whichEA];
        if(feta > 2.200 && feta < 2.300 ) return EA[4][whichEA];
        if(feta > 2.300 && feta < 2.400 ) return EA[5][whichEA];
        if(feta > 2.400 && feta < 10.00 ) return EA[6][whichEA];

        return -1;
}

double bbggTools::DeltaR(bbggTools::LorentzVector vec1, bbggTools::LorentzVector vec2)
{
//	double R2 = (vec1.phi() - vec2.phi())*(vec1.phi() - vec2.phi()) + (vec1.eta() - vec2.eta())*(vec1.eta() - vec2.eta());
//	return sqrt(R2);
	return deltaR(vec1, vec2);
}

bool bbggTools::isPhoID(edm::Ptr<flashgg::Photon> pho, vector<double> cuts)
{
    return bbggTools::isPhoID(pho.get(), cuts);
}

bool bbggTools::isPhoID(const flashgg::Photon* pho, vector<double> cuts)
{
	if(rho_ == -10 ){
		cout << "[bbggTools::isPhoID] You have to do tools->setRho(rho)!" << endl;
		return -1;
	}
	if(cuts.size() != 3){
		cout << "[bbggTools::isPhoID] ERROR: the input cuts vector must have size three (sieie/hoe/el-veto)" << endl;
		return 0;
	}
	bool isid = true;
	double hoe = pho->hadronicOverEm();
	double sieie = pho->full5x5_sigmaIetaIeta();

	if( hoe > cuts[0] ) 	isid = false;
  	if( sieie > cuts[1] ) isid = false;

	return isid;
}

bool bbggTools::isPhoISO(edm::Ptr<flashgg::DiPhotonCandidate> dipho, int whichPho, vector<double> cuts, vector<double> nhCorr, vector<double> phCorr)
{
	return bbggTools::isPhoISO(dipho.get(), whichPho, cuts, nhCorr, phCorr);
}

bool bbggTools::isPhoISO(const flashgg::DiPhotonCandidate * dipho, int whichPho, vector<double> cuts, vector<double> nhCorr, vector<double> phCorr)
{
	if(DEBUG) std::cout << "[bbggTools::isPhoISO] Doing cut based isolation!" << std::endl;

	if(rho_ == -10 ){
		cout << "[bbggTools::isPhoISO] You have to do tools->setRho(rho)!" << endl;
		return -1;
	}
	if(cuts.size() != 3){
		cout << "[bbggTools::isPhoISO] ERROR: the input cuts vector must have size three (ch/nh/ph)" << endl;
		return 0;
	}
	if(whichPho != 0 && whichPho != 1){
		cout << "[bbggTools::isPhoISO] ERROR: whichPho should be 0 (leading photon) or 1 (subleading photon)" << endl;
		return 0;
	}

  	double chiso = 0, nhiso = 0, phiso = 0;
	chiso = bbggTools::getCHisoToCutValue( dipho, whichPho);
	const flashgg::Photon* pho = (whichPho) ? dipho->subLeadingPhoton() : dipho->leadingPhoton();
	nhiso = bbggTools::getNHisoToCutValue( pho, nhCorr );
	phiso = bbggTools::getPHisoToCutValue( pho, phCorr );
	bool isiso = true;
	if(DEBUG) std::cout << "[bbggTools::isPhoISO] \t Before cuts: " << isiso << std::endl;
	if(chiso > cuts[0]) isiso = false;
	if(DEBUG) std::cout << "[bbggTools::isPhoISO] \t After chiso: " << isiso << std::endl;
	if(nhiso > cuts[1]) isiso = false;
	if(DEBUG) std::cout << "[bbggTools::isPhoISO] \t Before nhiso: " << isiso << std::endl;
	if(phiso > cuts[2]) isiso = false;
	if(DEBUG) std::cout << "[bbggTools::isPhoISO] \t Before phiso: " << isiso << std::endl;

	return isiso;

}


bool bbggTools::CheckCuts()
{
	if(	_PhotonPtOverDiPhotonMass.size() == 0 ||
		_PhotonEta.size() == 0 ||
		_PhotonDoID.size() == 0 ||
		_PhotonDoISO.size() == 0 ||
		_PhotonR9.size() == 0 ||
		_PhotonElectronVeto.size() == 0 ||
		_DiPhotonPt.size() == 0 ||
		_DiPhotonEta.size() == 0 ||
		_DiPhotonMassWindow.size() == 0 ||
		_JetPt.size() == 0 ||
		_JetEta.size() == 0 ||
		_JetBDiscriminant.size() == 0 ||
		_JetDrPho.size() == 0 ||
		_JetDoPUID.size() == 0 ||
		_DiJetPt.size() == 0 ||
		_DiJetEta.size() == 0 ||
		_DiJetMassWindow.size() == 0 ||
		_CandidateMassWindow.size() == 0 ||
		_CandidatePt.size() == 0 ||
		_CandidateEta.size() == 0 ||
		_CandidatesDeltaR.size() == 0 ||
        _PhotonDoElectronVeto.size() == 0 ) {
		return 0;
	} else {
		return 1;
	}
}

edm::Ptr<flashgg::DiPhotonCandidate> bbggTools::GetSelected_diphoCandidate()
{
	if(!hasDiPho){
		std::cout << "[bbggTools::GetSelected_diphoCandidate] ERROR: diphoCandidate has not been set yet. Run bbggTools::AnalysisSelection. If you did, then the event failed the selection requirements." << std::endl;
		return diphoCandidate;
	}
	return diphoCandidate;
}

edm::Ptr<flashgg::Jet> bbggTools::GetSelected_leadingJetCandidate()
{
	if(!hasLeadJet){
		std::cout << "[bbggTools::GetSelected_leadingJetCandidate] ERROR: leadingJetCandidate has not been set yet. Run bbggTools::AnalysisSelection. If you did, then the event failed the selection requirements." << std::endl;
		return leadingJetCandidate;
	}
	return leadingJetCandidate;
}

edm::Ptr<flashgg::Jet> bbggTools::GetSelected_subleadingJetCandidate()
{
	if(!hasLeadJet){
		std::cout << "[bbggTools::GetSelected_leadingJetCandidate] ERROR: leadingJetCandidate has not been set yet. Run bbggTools::AnalysisSelection. If you did, then the event failed the selection requirements." << std::endl;
		return subleadingJetCandidate;
	}
	return subleadingJetCandidate;
}


flashgg::Jet bbggTools::GetSelected_leadingJetCandidate_Ref()
{
	if(!hasLeadJet){
		std::cout << "[bbggTools::GetSelected_leadingJetCandidate] ERROR: leadingJetCandidate has not been set yet. Run bbggTools::AnalysisSelection. If you did, then the event failed the selection requirements." << std::endl;
		return leadingJetCandidate_Ref;
	}
	return leadingJetCandidate_Ref;
}


flashgg::Jet bbggTools::GetSelected_subleadingJetCandidate_Ref()
{
	if(!hasSubJet){
		std::cout << "[bbggTools::GetSelected_subleadingJetCandidate] ERROR: subleadingJetCandidate has not been set yet. Run bbggTools::AnalysisSelection. If you did, then the event failed the selection requirements." << std::endl;
		return subleadingJetCandidate_Ref;
	}
	return subleadingJetCandidate_Ref;
}

vector<flashgg::DiPhotonCandidate> bbggTools::DiPhotonKinematicSelection( vector<flashgg::DiPhotonCandidate> diphoCol, bool DoMassCut)
{
    vector<flashgg::DiPhotonCandidate> PreselDiPhotons;
    //Begin DiPhoton Loop/Selection -----------------------------------------------------------
    for( unsigned int diphoIndex = 0; diphoIndex < diphoCol.size(); diphoIndex++ )
    {

         if(DEBUG) std::cout << "[bbggTools::AnalysisSelection] Photon loop 1... " << diphoCol.size() << "\t" << diphoIndex << std::endl;

         if(_DiPhotonOnlyFirst && diphoIndex > 0 ) break;

         flashgg::DiPhotonCandidate dipho = diphoCol[ diphoIndex ];

         double dipho_pt = dipho.pt();
         double dipho_eta = dipho.eta();
         double dipho_mass = dipho.mass();

     //Cuts on diphoton object
         if(DoMassCut){
             if(dipho_mass < _DiPhotonMassWindow[0] || dipho_mass > _DiPhotonMassWindow[1])
                 continue;
         }
         if(fabs(dipho_eta) > _DiPhotonEta[0] ) continue;
         if(dipho_pt < _DiPhotonPt[0] ) continue;

     //Cuts on photons
         double pho1_pt = dipho.leadingPhoton()->pt();
         if( pho1_pt < dipho_mass*_PhotonPtOverDiPhotonMass[0] ) continue;

         double pho2_pt = dipho.subLeadingPhoton()->pt();
         if( pho2_pt < dipho_mass*_PhotonPtOverDiPhotonMass[1] ) continue;

         double pho1_eta = dipho.leadingPhoton()->superCluster()->eta();
         if( fabs(pho1_eta) > _PhotonEta[1] ) continue;

         double pho2_eta = dipho.subLeadingPhoton()->superCluster()->eta();
         if( fabs(pho2_eta) > _PhotonEta[1] ) continue;

	 PreselDiPhotons.push_back(dipho);

     }

     return PreselDiPhotons;

}

vector<flashgg::DiPhotonCandidate> bbggTools::DiPhotonIDSelection( vector<flashgg::DiPhotonCandidate> diphoCol)
{
    vector<pair<flashgg::DiPhotonCandidate, int > > SelectedDiPhotons = bbggTools::EvaluatePhotonIDs( diphoCol);
    if (DEBUG){
	std::cout << "[bbggTools::DiPhotonIDSelection] Selected photons" << std::endl;
	int di = 0;
	for ( vector<pair<flashgg::DiPhotonCandidate, int > >::const_iterator it = SelectedDiPhotons.begin();
            it != SelectedDiPhotons.end(); it++){
		std::cout << "\t Diphoton " << di << " -- ID: " << it->second << std::endl;
		di++;
   	}
    }
    vector<flashgg::DiPhotonCandidate> SignalDiPhotons = bbggTools::GetDiPhotonsInCategory(SelectedDiPhotons, 2);

    return SignalDiPhotons;
}

vector<flashgg::DiPhotonCandidate> bbggTools::GetDiPhotonsInCategory( vector<pair<flashgg::DiPhotonCandidate, int > > SelectedDiPhotons, int category )
{
    vector<flashgg::DiPhotonCandidate> catDiPhotons;
    for ( vector<pair<flashgg::DiPhotonCandidate, int > >::const_iterator it = SelectedDiPhotons.begin();
            it != SelectedDiPhotons.end(); it++){
        if(it->second == category){
            catDiPhotons.push_back(it->first);
        }
    }
    return catDiPhotons;
}

vector<pair<flashgg::DiPhotonCandidate, int > > bbggTools::EvaluatePhotonIDs( vector<flashgg::DiPhotonCandidate> diphoCol, unsigned int doCustomID,unsigned int doTnP)
{
  indexSel_=-1;
   vector<pair<flashgg::DiPhotonCandidate, int > > PreselDiPhotons;
    //Begin DiPhoton Loop/Selection -----------------------------------------------------------
   for( unsigned int diphoIndex = 0; diphoIndex < diphoCol.size(); diphoIndex++ )
   {
         if(DEBUG) std::cout << "[bbggTools::AnalysisSelection] Photon loop 2..." << std::endl;
         flashgg::DiPhotonCandidate dipho = diphoCol[ diphoIndex ];

         int pho_elv[2];
         pho_elv[0] = dipho.leadingPhoton()->passElectronVeto();
         pho_elv[1] = dipho.subLeadingPhoton()->passElectronVeto();

         double pho1_eta = dipho.leadingPhoton()->superCluster()->eta();
	 double pho2_eta = dipho.subLeadingPhoton()->superCluster()->eta();

         float pho_mvas[2];
         if( doCustomID ) {
            if(DEBUG) std::cout << "[bbggTools::EvaluatePhotonIDs] doing custom MVA cut " << std::endl;
            pho_mvas[0] = dipho.leadingPhoton()->phoIdMvaDWrtVtx( dipho.vtx() );
            pho_mvas[1] = dipho.subLeadingPhoton()->phoIdMvaDWrtVtx( dipho.vtx() );
         } else {
            pho_mvas[0] = dipho.leadingPhoton()->userFloat(_PhotonMVAEstimator);
            pho_mvas[1] = dipho.subLeadingPhoton()->userFloat(_PhotonMVAEstimator);
         }

         int pho_ids[2];
         pho_ids[0] = 1;
         pho_ids[1] = 1;
         if(DEBUG) std::cout << "[bbggTools::AnalysisSelection] Photon loop 3..." << std::endl;
         for( int whichPho = 0; whichPho < 2; whichPho++)
         {
             if( _PhotonDoElectronVeto[whichPho] ) {
	       if(!doTnP) pho_ids[whichPho] = pho_elv[whichPho];
	       else pho_ids[whichPho] = pho_elv[whichPho] > 0 ? 0:1;
             }
             int pho1Index = 0; //Index 0 = barrel, 1 = endcap
             double pho_eta = (whichPho) ? fabs(pho2_eta) : fabs(pho1_eta);
             if( pho_eta > _PhotonEta[0] ) pho1Index = 1;

             if(_DoMVAPhotonID){
		if(DEBUG) std::cout << "[bbggTools::::EvaluatePhotonIDs] Doing MVA ID!" << std::endl;
                if(DEBUG) std::cout << pho_mvas[whichPho] << " " <<  _MVAPhotonID[pho1Index];
                if( pho_mvas[whichPho] < _MVAPhotonID[pho1Index] ){
                    pho_ids[whichPho] = 0;
                }
                continue;
             }
/*
             if( _PhotonDoID[whichPho] && _DoMVAPhotonID == 0)
             {
 		 if(DEBUG) std::cout << "[bbggTools::::EvaluatePhotonIDs] Doing Cut Based ID!" << std::endl;
                 std::map<int, vector<double> > theIDWP = bbggTools::getWhichID(_phoWhichID[whichPho]);
                 if(theIDWP.size() < 1) break;

                 int pho1_id = (whichPho) ? bbggTools::isPhoID(dipho.subLeadingPhoton(), theIDWP[pho1Index]) : bbggTools::isPhoID(dipho.leadingPhoton(), theIDWP[pho1Index]) ;
                 if (!pho1_id) pho_ids[whichPho] = 0;
		 if(DEBUG) std::cout << "[bbggTools::::EvaluatePhotonIDs] \t Result: " << pho_ids[whichPho] << std::endl;
             }
             if(_PhotonDoISO[whichPho] && _DoMVAPhotonID == 0)
             {
		 if(DEBUG) std::cout << "[bbggTools::::EvaluatePhotonIDs] Doing Cut Based ISO!" << std::endl;
                 std::map<int, vector<double> > theISOWP = bbggTools::getWhichISO(_phoWhichISO[whichPho]);
                 if(theISOWP.size() < 1) break;

                 int pho1_id = bbggTools::isPhoISO(dipho, whichPho, theISOWP[pho1Index], _nhCorr[pho1Index], _phCorr[pho1Index]);
                 if (!pho1_id) pho_ids[whichPho] = 0;
		 if(DEBUG) std::cout << "[bbggTools::::EvaluatePhotonIDs] \t Result: " << pho_ids[whichPho] << std::endl;
             }//here
*/
         }
         if(DEBUG) std::cout << "[bbggTools::AnalysisSelection] After Photon loop..." << std::endl;

         //Category = 0: no id'ed photons
         //Category = 1: 1 id'ed photon (fake photon CR)
         //Category = 2: 2 id'ed photons (signal region)
         int Category = pho_ids[0] + pho_ids[1];
         PreselDiPhotons.push_back(make_pair(dipho, Category));
	 if (Category == 2){
	   indexSel_=diphoIndex;
	 }
     }
     return PreselDiPhotons;
}

std::vector<flashgg::Jet> bbggTools::DiJetSelection(std::vector<std::pair<flashgg::Jet, flashgg::Jet>> Jets, bool DoMassCut)
{


    flashgg::Jet jet1, jet2;
    std::vector<flashgg::Jet> SelDijet;
    bbggTools::LorentzVector DiJet(0,0,0,0);
    double sumbtag_ref = -999;
//    bool hasDiJet = false;
    sumbtag_ref = sumbtag_ref;

    if(DEBUG) std::cout << "Jet sorting... " << std::endl;
    for(unsigned int dj = 0; dj < Jets.size(); dj++)
    {
       flashgg::Jet lJet = Jets[dj].first;
       flashgg::Jet sJet = Jets[dj].second;
       bbggTools::LorentzVector diJet = lJet.p4() + sJet.p4();
       if(DoMassCut){
         if(diJet.mass() < _DiJetMassWindow[0] || diJet.mass() > _DiJetMassWindow[1]) continue;
       }
       if(diJet.pt() < _DiJetPt[0]) continue;
       if(fabs(diJet.eta()) > _DiJetEta[0]) continue;

//       if( lJet.pt() < 50 && sJet.pt() < 50) continue;

       double sumbtag = lJet.bDiscriminator(_bTagType) + sJet.bDiscriminator(_bTagType);
       if (sumbtag > sumbtag_ref) {
         sumbtag_ref = sumbtag;
         jet1 = lJet;
         jet2 = sJet;
       }

/*
 		for(unsigned int jJet = iJet+1; jJet < Jets.size(); jJet++)
 		{
 	  		bbggTools::LorentzVector dijet = Jets[iJet].p4() + Jets[jJet].p4();
            		if(DoMassCut){
		                if(dijet.mass() < _DiJetMassWindow[0] || dijet.mass() > _DiJetMassWindow[1]) continue;
		        }

			double sumbtag = Jets[iJet].bDiscriminator(_bTagType) + Jets[jJet].bDiscriminator(_bTagType);

 	  		if(sumbtag > sumbtag_ref && dijet.pt() > _DiJetPt[0] && fabs(dijet.Eta()) < _DiJetEta[0] )
 	  		{
				hasDiJet = true;
				sumbtag_ref = sumbtag;
				if( Jets[iJet].pt() > Jets[jJet].pt() ) {
					jet1 = Jets.at(iJet);
					jet2 = Jets.at(jJet);
				} else {
					jet2 = Jets.at(iJet);
					jet1 = Jets.at(jJet);
				}
			}
		}
*/
	}

	if(sumbtag_ref > -999){
		SelDijet.push_back(jet1);
		SelDijet.push_back(jet2);
	}
	return SelDijet;

}

std::vector<flashgg::Jet> bbggTools::DiJetSelection(std::vector<flashgg::Jet> Jets, bool DoMassCut)
{


    flashgg::Jet jet1, jet2;
    std::vector<flashgg::Jet> SelDijet;
    bbggTools::LorentzVector DiJet(0,0,0,0);
    double sumbtag_ref = -999;
    bool hasDiJet = false;
    sumbtag_ref = sumbtag_ref;

    if(DEBUG) std::cout << "Jet sorting... " << std::endl;
    for(unsigned int iJet = 0; iJet < Jets.size(); iJet++)
    {
 		unsigned int isbjet = 0;
 		if( Jets[iJet].bDiscriminator(_bTagType) > _JetBDiscriminant[1] ) isbjet = 1;
 		for(unsigned int jJet = iJet+1; jJet < Jets.size(); jJet++)
 		{
 	  	 	unsigned int isbjet2 = 0;
 	  		if( Jets[jJet].bDiscriminator(_bTagType) > _JetBDiscriminant[1] ) isbjet2 = 1;
 	  		unsigned int totalbjet = isbjet + isbjet2;
 	  		if(_n_bJets && totalbjet != _n_bJets) continue;

 	  		bbggTools::LorentzVector dijet = Jets[iJet].p4() + Jets[jJet].p4();
            		if(DoMassCut){
		                if(dijet.mass() < _DiJetMassWindow[0] || dijet.mass() > _DiJetMassWindow[1]) continue;
		        }

			double sumbtag = Jets[iJet].bDiscriminator(_bTagType) + Jets[jJet].bDiscriminator(_bTagType);

 	  		if(sumbtag > sumbtag_ref && dijet.pt() > _DiJetPt[0] && fabs(dijet.Eta()) < _DiJetEta[0] )
 	  		{
				hasDiJet = true;
				sumbtag_ref = sumbtag;
				if( Jets[iJet].pt() > Jets[jJet].pt() ) {
					jet1 = Jets.at(iJet);
					jet2 = Jets.at(jJet);
				} else {
					jet2 = Jets.at(iJet);
					jet1 = Jets.at(jJet);
				}
			}
		}
	}

	if(hasDiJet){
		SelDijet.push_back(jet1);
		SelDijet.push_back(jet2);
	}
	return SelDijet;

}




std::vector<flashgg::Jet> bbggTools::DiJetVBFSelection(std::vector<flashgg::Jet> Jets, std::vector<flashgg::Jet> DiJet)
{


    flashgg::Jet jet1, jet2;
    std::vector<flashgg::Jet> SelDijet;
    double sumbtag_ref = -999;
    bool hasDiJet = false;
    sumbtag_ref = sumbtag_ref;

    double deta_max = 0; 
    int iJet_vbf = -1, jJet_vbf = -1;

    if(DEBUG) std::cout << "Jet sorting... " << std::endl;


    for(unsigned int iJet = 0; iJet < Jets.size(); iJet++) {

      for(unsigned int jJet = iJet+1; jJet < Jets.size(); jJet++) {

	double deta = fabs(Jets[iJet].p4().eta() - Jets[jJet].p4().eta());

	//	std::cout << "Jets[iJet].p4().eta() = " << Jets[iJet].p4().eta() << " Jets[jJet].p4().eta() = " << Jets[jJet].p4().eta() << " deta = " << deta << endl;

	if (deta > deta_max) {
	  deta_max = deta;
	  iJet_vbf = iJet; jJet_vbf = jJet; 
	  hasDiJet = true;
	}

      }

    }

    if (hasDiJet){
      if( Jets[iJet_vbf].pt() > Jets[jJet_vbf].pt() ) {
	jet1 = Jets.at(iJet_vbf);
	jet2 = Jets.at(jJet_vbf);
      } else {
	jet2 = Jets.at(iJet_vbf);
	jet1 = Jets.at(jJet_vbf);
      }

      SelDijet.push_back(jet1);
      SelDijet.push_back(jet2);

    }
     
    //   std::cout << "" << endl;

    return SelDijet;



}


std::vector<float> bbggTools::XttCalculation(std::vector<flashgg::Jet> allJetsCol, std::vector<flashgg::Jet> DiJet)
{
  std::vector<flashgg::Jet> jetsCol;
  for( unsigned int jetIndex = 0; jetIndex < allJetsCol.size(); jetIndex++ )
    {
      flashgg::Jet *jet = &(allJetsCol[jetIndex]);
      bool bExtraJet = isExtraJet(jet, DiJet);

      if (!bExtraJet) continue;
      jetsCol.push_back(*jet );
     }
    

  std::vector<float> Xtt;
  Xtt.push_back(1000);  Xtt.push_back(0);   Xtt.push_back(0);  Xtt.push_back(1000); Xtt.push_back(0);  Xtt.push_back(0); 
  unsigned int WJetIndex00 = 1000,  WJetIndex01 = 1000, bJetIndex0 = 1000;

  
  for( unsigned int jetIndex0 = 0; jetIndex0 < jetsCol.size(); jetIndex0++ ) {
      //flashgg::Jet jet = jetsCol[jetIndex];
      const flashgg::Jet *jet0 = &(jetsCol[jetIndex0]);
      for( unsigned int jetIndex1 = jetIndex0+1; jetIndex1 < jetsCol.size(); jetIndex1++ ) {
	 const flashgg::Jet *jet1 = &(jetsCol[jetIndex1]);
         
	 LorentzVector Wcand = jet0->p4() + jet1->p4();
	 LorentzVector tcand0 = Wcand + DiJet[0].p4();
	 LorentzVector tcand1 = Wcand + DiJet[1].p4();
	 
	 float XW = TMath::Power((Wcand.M() - mW)/(0.1*mW),2);
	 float XT0 = XW + TMath::Power((tcand0.M() - mt)/(0.1*mt),2);
	 float XT1 = XW + TMath::Power((tcand1.M() - mt)/(0.1*mt),2);

	 if (Xtt[0] > XT0) {
	   Xtt[0] = XT0; Xtt[1] = Wcand.M(); Xtt[2] = tcand0.M(); 
	   WJetIndex00 = jetIndex0, WJetIndex01 = jetIndex1, bJetIndex0 = 0;
	 }
	 if (Xtt[0] > XT1) {
	   Xtt[0] = XT1; Xtt[1] = Wcand.M(); Xtt[2] = tcand1.M(); 
	   WJetIndex00 = jetIndex0, WJetIndex01 = jetIndex1, bJetIndex0 = 1;
	 }
      }
    }

  if (jetsCol.size() < 4) return Xtt;
  
  int  bJetIndex = 0;
  if ( bJetIndex0 == 0) bJetIndex = 1;
   
   for( unsigned int jetIndex0 = 0; jetIndex0 < jetsCol.size(); jetIndex0++ ) {
      //flashgg::Jet jet = jetsCol[jetIndex];
      const flashgg::Jet *jet0 = &(jetsCol[jetIndex0]);
	
      for( unsigned int jetIndex1 = jetIndex0+1; jetIndex1 < jetsCol.size(); jetIndex1++ ) {
	  
	if( ( WJetIndex00 == jetIndex0 && WJetIndex01 == jetIndex1 ) || 
	    ( WJetIndex01 == jetIndex0 && WJetIndex00 == jetIndex1 )) continue;

	 const flashgg::Jet *jet1 = &(jetsCol[jetIndex1]);

	 LorentzVector Wcand = jet0->p4() + jet1->p4();
	 LorentzVector tcand = Wcand + DiJet[bJetIndex].p4();

	 float XW = TMath::Power((Wcand.M() - mW)/(0.1*mW),2);
	 float XT = XW + TMath::Power((tcand.M() - mt)/(0.1*mt),2);

	 if (Xtt[3] > XT) {
	   Xtt[3] = XT;  Xtt[4] = Wcand.M(); Xtt[5] = tcand.M(); 
	 }

      }
    }
  
  
   return Xtt;
}



std::vector<flashgg::Jet> bbggTools::JetVBFPreSelection(std::vector<flashgg::Jet> jetsCol, flashgg::DiPhotonCandidate dCand, std::vector<flashgg::Jet> DiJet)
{

    //Begin Jets Loop/Selection ------------------------------------------------------------
    std::vector<flashgg::Jet> Jets;
    if(DEBUG) std::cout << "Begin Jet selection..." << std::endl;
    for( unsigned int jetIndex = 0; jetIndex < jetsCol.size(); jetIndex++ )
    {
      //flashgg::Jet jet = jetsCol[jetIndex];
      const flashgg::Jet *jet = &(jetsCol[jetIndex]);

    	bool isJet = true;

        if(_JetDoID[0] && !(bbggTools::isJetID(jet)))
            isJet = false;
        // if( _JetDoPUID[0]  )
        //            isJet = false;
    	if(jet->pt() < _JetPt[0])
            isJet = false;
 	if( !isJet )
            continue;
 	if( bbggTools::DeltaR(jet->p4(), dCand.leadingPhoton()->p4()) < _JetDrPho[0]
	    || bbggTools::DeltaR(jet->p4(), dCand.subLeadingPhoton()->p4()) < _JetDrPho[0] ) {
	  //	  cout << "Matched to photon" << endl;
	  continue;
	}
	bool bExtraJet = isExtraJet(jet, DiJet);

	if (!bExtraJet) continue;
	Jets.push_back(*jet );
     }

    if(DEBUG)    cout << "VBF jets candidate size" << Jets.size() << endl;

return Jets;
}


bool bbggTools::isExtraJet(const flashgg::Jet *jet,  std::vector<flashgg::Jet> DiJet)
{
   bool isSel = 1;
   if( bbggTools::DeltaR(jet->p4(), DiJet[0].p4()) < 0.1
       || bbggTools::DeltaR(jet->p4(), DiJet[1].p4()) < 0.1 ) 
     isSel = 0;

   return isSel;
}

bool bbggTools::SingleJetPreSelection(flashgg::Jet jet, flashgg::DiPhotonCandidate dipho)
{
   bool isSel = 1;
   if (jet.pt() < _JetPt[0]) isSel = 0;
   if (fabs(jet.eta()) > _JetEta[0]) isSel = 0;
   if (_JetDoID[0] && !(bbggTools::isJetID(&jet))) isSel = 0;
   if (jet.bDiscriminator(_bTagType) < _JetBDiscriminant[0]) isSel = 0;
   if( bbggTools::DeltaR(jet.p4(), dipho.leadingPhoton()->p4()) < _JetDrPho[0]
             || bbggTools::DeltaR(jet.p4(), dipho.subLeadingPhoton()->p4()) < _JetDrPho[0] ) isSel = 0;

   return isSel;
}


std::vector<flashgg::Jet> bbggTools::JetPreSelection(std::vector<flashgg::Jet> jetsCol, flashgg::DiPhotonCandidate dCand)
{

    //Begin Jets Loop/Selection ------------------------------------------------------------
    std::vector<flashgg::Jet> Jets;
    if(DEBUG) std::cout << "Begin Jet selection..." << std::endl;
    for( unsigned int jetIndex = 0; jetIndex < jetsCol.size(); jetIndex++ )
    {
        const flashgg::Jet jet = jetsCol[jetIndex];
/*
        if(_JetDoID[0] && !(bbggTools::isJetID(jet))) continue;
    	if(fabs(jet->eta()) > _JetEta[0] ) continue;
    	if(jet->pt() < _JetPt[0]) continue;
 	if(jet->bDiscriminator(_bTagType) < _JetBDiscriminant[0]) continue;

 	if( bbggTools::DeltaR(jet->p4(), dCand.leadingPhoton()->p4()) < _JetDrPho[0]
             || bbggTools::DeltaR(jet->p4(), dCand.subLeadingPhoton()->p4()) < _JetDrPho[0] ) continue;
*/      bool isSel = bbggTools::SingleJetPreSelection(jet, dCand);
        if(isSel) Jets.push_back(jet);
     }

return Jets;
}





std::vector<std::pair<flashgg::Jet, flashgg::Jet>> bbggTools::JetPreSelection(std::vector<std::pair<flashgg::Jet,flashgg::Jet>> jetsCol, flashgg::DiPhotonCandidate dCand)
{

    //Begin Jets Loop/Selection ------------------------------------------------------------
    std::vector<std::pair<flashgg::Jet, flashgg::Jet>> Jets;
    if(DEBUG) std::cout << "Begin Jet selection..." << std::endl;
    for( unsigned int jetIndex = 0; jetIndex < jetsCol.size(); jetIndex++ )
    {
        const flashgg::Jet ljet = jetsCol[jetIndex].first;
        const flashgg::Jet sjet = jetsCol[jetIndex].second;

        bool isLSel = bbggTools::SingleJetPreSelection(ljet, dCand);
        bool isSSel = bbggTools::SingleJetPreSelection(sjet, dCand);

        if(isLSel && isSSel ) Jets.push_back( jetsCol[jetIndex]  );
     }

return Jets;
}


flashgg::DiPhotonCandidate bbggTools::MVAIDDiPhotonSelection( vector<flashgg::DiPhotonCandidate> DiPhotons)
{
	float sumMVA_ref = -999;
	unsigned int maxId = -1;
	if(DEBUG) std::cout << "[bbggTools::MVAIDDiPhotonSelection] Number of diphotons: " << DiPhotons.size() << std::endl;
	for( unsigned int p = 0; p < DiPhotons.size(); p++  )
	{
		flashgg::DiPhotonCandidate it = DiPhotons[p];
		float sumMVA = it.leadingPhoton()->userFloat(_PhotonMVAEstimator) + it.subLeadingPhoton()->userFloat(_PhotonMVAEstimator);
		if(DEBUG) std::cout << "[bbggTools::MVAIDDiPhotonSelection] Diphoton " << p << " sum mva: " << sumMVA << std::endl;
		if(sumMVA > sumMVA_ref){
			sumMVA_ref = sumMVA;
			maxId = p;
		}
	}

	if(DEBUG) std::cout << "[bbggTools::MVAIDDiPhotonSelection] Selected diphoton index: " << maxId << std::endl;
	return DiPhotons[maxId];
}

flashgg::DiPhotonCandidate bbggTools::PtSumDiPhotonSelection( vector<flashgg::DiPhotonCandidate> DiPhotons)
{
	float sumPt_ref = 0;
	unsigned int maxId = -1;
	for( unsigned int p = 0; p < DiPhotons.size(); p++  )
	{
		flashgg::DiPhotonCandidate it = DiPhotons[p];
		float sumPt = it.leadingPhoton()->pt() + it.subLeadingPhoton()->pt();
		if(sumPt > sumPt_ref){
			sumPt_ref = sumPt;
			maxId = p;
		}
	}

	return DiPhotons[maxId];
}

std::vector<edm::Ptr<flashgg::Muon> > bbggTools::filterMuons( const std::vector<edm::Ptr<flashgg::Muon> > &muonPointers, 
							      flashgg::DiPhotonCandidate dipho, 
							      LorentzVector leadingJet, LorentzVector subleadingJet,
							      double dRPhoLeptonThreshold, double dRJetLeptonThreshold){

  std::vector<edm::Ptr<flashgg::Muon> > goodMuons;

  double Phi_Pho1 = dipho.leadingPhoton()->superCluster()->phi();
  double Phi_Pho2 = dipho.subLeadingPhoton()->superCluster()->phi();
  double Eta_Pho1 = dipho.leadingPhoton()->superCluster()->eta();
  double Eta_Pho2 = dipho.subLeadingPhoton()->superCluster()->eta();

  double Phi_Jet1 =  leadingJet.Phi();
  double Phi_Jet2 =  subleadingJet.Phi();
  double Eta_Jet1 =  leadingJet.Eta();
  double Eta_Jet2 =  subleadingJet.Eta();

  for( unsigned int muonIndex = 0; muonIndex < muonPointers.size(); muonIndex++ ) {
    edm::Ptr<flashgg::Muon> muon = muonPointers[muonIndex];
    double Eta_Lepton = muon->eta(), Phi_Lepton = muon->phi();

    float dRLeadPhoLepton      = deltaR( Eta_Lepton, Phi_Lepton, Eta_Pho1, Phi_Pho1);
    float dRSubLeadPhoLepton   = deltaR( Eta_Lepton, Phi_Lepton, Eta_Pho2, Phi_Pho2);
    
    float dRLeadJetLepton    = deltaR( Eta_Lepton, Phi_Lepton, Eta_Jet1, Phi_Jet1);
    float dRSubLeadJetLepton = deltaR( Eta_Lepton, Phi_Lepton, Eta_Jet2, Phi_Jet2);

    
    if( dRLeadPhoLepton < dRPhoLeptonThreshold || dRSubLeadPhoLepton < dRPhoLeptonThreshold || 
	dRLeadJetLepton < dRJetLeptonThreshold || dRSubLeadJetLepton < dRJetLeptonThreshold) continue; 
    
    goodMuons.push_back( muon );
  }
  return goodMuons;
  
}



std::vector<edm::Ptr<flashgg::Electron> > bbggTools::filterElectrons( const std::vector<edm::Ptr<flashgg::Electron> > &electronPointers, 
								      flashgg::DiPhotonCandidate dipho, 
								      LorentzVector leadingJet, LorentzVector subleadingJet,
								      double dRPhoLeptonThreshold, double dRJetLeptonThreshold){

  std::vector<edm::Ptr<flashgg::Electron> > goodElectrons;

  double Phi_Pho1 = dipho.leadingPhoton()->superCluster()->phi();
  double Phi_Pho2 = dipho.subLeadingPhoton()->superCluster()->phi();
  double Eta_Pho1 = dipho.leadingPhoton()->superCluster()->eta();
  double Eta_Pho2 = dipho.subLeadingPhoton()->superCluster()->eta();

  double Phi_Jet1 =  leadingJet.Phi();
  double Phi_Jet2 =  subleadingJet.Phi();
  double Eta_Jet1 =  leadingJet.Eta();
  double Eta_Jet2 =  subleadingJet.Eta();

  for( unsigned int electronIndex = 0; electronIndex < electronPointers.size(); electronIndex++ ) {
    edm::Ptr<flashgg::Electron> electron = electronPointers[electronIndex];
    double Eta_Lepton = electron->superCluster()->eta(), Phi_Lepton = electron->superCluster()->phi();

    float dRLeadPhoLepton      = deltaR( Eta_Lepton, Phi_Lepton, Eta_Pho1, Phi_Pho1);
    float dRSubLeadPhoLepton   = deltaR( Eta_Lepton, Phi_Lepton, Eta_Pho2, Phi_Pho2);
    
    float dRLeadJetLepton    = deltaR( Eta_Lepton, Phi_Lepton, Eta_Jet1, Phi_Jet1);
    float dRSubLeadJetLepton = deltaR( Eta_Lepton, Phi_Lepton, Eta_Jet2, Phi_Jet2);

    
    if( dRLeadPhoLepton < dRPhoLeptonThreshold || dRSubLeadPhoLepton < dRPhoLeptonThreshold || 
	dRLeadJetLepton < dRJetLeptonThreshold || dRSubLeadJetLepton < dRJetLeptonThreshold) continue; 
    
    goodElectrons.push_back( electron );
  }
  return goodElectrons;
  
}

