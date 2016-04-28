void makeEpsilonGraph(){

	ifstream recX1;
	recX1.open("recX1.txt");
	ifstream recX2;
	recX2.open("recX2.txt");
	ifstream recX3;
	recX3.open("recX3.txt");
	ifstream recY1;
	recY1.open("recY1.txt");
	ifstream recY2;
	recY2.open("recY2.txt");
	ifstream recY3;
	recY3.open("recY3.txt");

	double valrecX1;
	double valrecX2;
	double valrecX3;
	double valrecY1;
	double valrecY2;
	double valrecY3;

	int iteracja1=0;
	int iteracja2=0;
	int iteracja3=0;

	TGraph *graph1 = new TGraph();	
	TGraph *graph2 = new TGraph();	
	TGraph *graph3 = new TGraph();	

	while(recX1>>valrecX1){
		recY1>>valrecY1;
		graph1->SetPoint(iteracja1, valrecX1, valrecY1);
		iteracja1++;
	}
	recX1.close();
	recY1.close();

	while(recX2>>valrecX2){
		recY2>>valrecY2;
		graph2->SetPoint(iteracja2, valrecX2, valrecY2);
		iteracja2++;
	}
	recX2.close();
	recY2.close();

	while(recX3>>valrecX3){
		recY3>>valrecY3;
		graph3->SetPoint(iteracja3, valrecX3, valrecY3);
		iteracja3++;
	}
	recX3.close();
	recY3.close();

	graph3->SetTitle("Recursive diagram");
	graph1->GetXaxis()->SetTitle("f(x)");
	graph1->GetYaxis()->SetTitle("f(x)");

	TCanvas *c1 = new TCanvas("c1","Lab1",10,10,800,800);
	c1->Divide(1,1);
	c1->cd(1);
	graph2->SetMarkerColor(3);
	graph3->SetMarkerColor(4);
	//graph1->SetMarkerColor(5);
	graph3->Draw("AP");
	graph2->Draw("samep");
	graph1->Draw("samep");
	
	
	/*
	leg = new TLegend(0.1,0.7,0.48,0.9);
	leg->SetHeader("The Legend Title");
	leg->AddEntry("gr","Graph with error bars","lep");
	leg->Draw();
	*/

	c1->update();
}
