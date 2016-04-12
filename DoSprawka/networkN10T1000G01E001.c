void networkN10T1000G01E001(){
	ifstream ifile;
	ifile.open("networkN10T1000G01E001.txt");
	double val;
	double g=0;
	int pointNumber=0;
	TGraph *graph = new TGraph();
	
	while(ifile>>val){
		graph->SetPoint(pointNumber, g, val);
		g+=0.0001;
		pointNumber++;
	}
	ifile.close();

	graph->SetTitle("Entropia sieci dla N=10, T=1000, e=0.01, A=3 (g)");
	graph->GetXaxis()->SetTitle("g");
	graph->GetYaxis()->SetTitle("Entropia");
	
	ifstream ifile2;
	ifile2.open("networkN10T1000G01E001A0.txt");
	double val2;
	double g2=0;
	int pointNumber2=0;
	TGraph *graph2 = new TGraph();

	while(ifile2>>val2){
		graph2->SetPoint(pointNumber2, g2, val2);
		g2+=0.0001;
		pointNumber2++;
	}
	ifile2.close();

	graph2->SetTitle("Entropia sieci dla N=10, T=1000, e=0.01, A=0 (g)");
	graph2->GetXaxis()->SetTitle("g");
	graph2->GetYaxis()->SetTitle("Entropia");
	
	TCanvas *c1 = new TCanvas("c1","Lab1",10,10,800,800);
	c1->Divide(1,2);
	c1->cd(1);
	graph->Draw();
	c1->cd(2);
	graph2->Draw();
}
