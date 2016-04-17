void sigmaG0008(){
	ifstream ifile;
	ifile.open("sigma1.txt");
	double val;
	double g=0;
	int pointNumber=0;
	TGraph *graph = new TGraph();
	
	while(ifile>>val){
		graph->SetPoint(pointNumber, g, val);
		g+=0.001;
		pointNumber++;
	}
	ifile.close();

	graph->SetTitle("Sigma(t) dla g =0.008 A=0");
	graph->GetXaxis()->SetTitle("t");
	graph->GetYaxis()->SetTitle("Sigma");

	
	TCanvas *c1 = new TCanvas("c1","Lab1",10,10,800,800);
	c1->Divide(1,1);
	c1->cd(1);
	graph->Draw();
}
