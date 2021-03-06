void sigmaG0008(){
	ifstream ifile1;
	ifstream ifile2;
	ifile1.open("returnsMapX.txt");
	ifile2.open("returnsMapY.txt");
	double valX;
	double valY;
	double g=0;
	int pointNumber=0;
	TGraph *graph = new TGraph();
	
	while(ifile1>>valX){
		ifile2>>valY;
		graph->SetPoint(pointNumber, valX, valY);
		pointNumber++;
	}
	ifile1.close();
	ifile2.close();

	graph->SetTitle("Entropia od g");
	graph->GetXaxis()->SetTitle("g");
	graph->GetYaxis()->SetTitle("Entropia");
	
	
	TCanvas *c1 = new TCanvas("c1","Lab1",10,10,800,800);
	c1->Divide(1,1);
	c1->cd(1);
	graph->Draw("AP");
	graph->SetMarkerStyle(8);
	c1->update();
}
