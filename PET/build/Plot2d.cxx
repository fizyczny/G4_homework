void Plot2d()
{
    //otwarcie pliku
    TFile* f = new TFile("POS.root");
    TTree* t=(TTree*)f->Get("PosInfo");

    double xMin = -600;
    double xMax = 600;
    int nBinsX = 1*(xMax-xMin);
    double yMin = -600;
    double yMax = 600;
    int nBinsY = 1*(yMax-yMin);
    double zMin = 0;
    double zMax = 1;
    int nBinsZ = 100*(zMax-zMin);
    TH3F* IdId = new TH3F("IdId","Pos_en",nBinsX,xMin,xMax, nBinsY, yMin, yMax,nBinsZ, zMin, zMax);
    gStyle->SetOptStat(0);//brak legendy
    t->Draw("energy:pos_y:pos_x>>IdId");
    IdId->Draw("IdId");
}
