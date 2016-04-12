void entropyFromGinLM(){
	ifstream ifile;
	ifile.open("logisticMapEntropyFromG.txt");
	double val;
	double g=3.5;
	int pointNumber=0;
	TGraph *graph = new TGraph();
	
	while(ifile>>val){
		graph->SetPoint(pointNumber, g, val);
		g+=0.0005;
		pointNumber++;
	}
	ifile.close();

	graph->SetTitle("Entropia(g)");
	graph->GetXaxis()->SetTitle("g");
	graph->GetYaxis()->SetTitle("Entropia");

	TCanvas *c1 = new TCanvas("c1","Lab1",10,10,800,800);
	c1->Divide(1,1);
	c1->cd(1);
	graph->Draw();
}
