#include <iostream>
#include <string>
using namespace std;
class House
{
private:
    bool base = false;
    bool building = false;
    bool serviceLines = false;
    bool finish = false;
public:
    bool IsBase() {return base;}
    void SetBase(bool base) {this->base = base;}
    bool IsBuilding() {return building;}
    void SetBuilding(bool building) {this->building = building;}
    bool IsServiceLines() {return serviceLines;}
    void SetServiceLines(bool serviceLines) {this->serviceLines = serviceLines;}
    bool IsFinish() {return finish;}
    void SetFinish(bool finish) {this->finish = finish;}

    string YesNo(bool r){return r ? "Yes" : "No";}

    string ToString()
    {
        string sb;
        string result;

        sb.append("Base: ");
        result.append(YesNo(IsBase()));
        sb.append(result);
        sb.append("\n");
        result.clear();

        sb.append("Building: ");
        result.append(YesNo(IsBuilding()));
        sb.append(result);
        sb.append("\n");
        result.clear();

        sb.append("ServiceLines: ");
        result.append(YesNo(IsServiceLines()));
        sb.append(result);
        sb.append("\n");
        result.clear();

        sb.append("Finish: ");
        result.append(YesNo(IsFinish()));
        sb.append(result);
        sb.append("\n");
        result.clear();

        return sb;
    }
};

class Documentation
{
private:
    bool base = false;
    bool building = false;
    bool serviceLines = false;
    bool finish = false;
public:
    bool IsBase() {return base;}
    void SetBase(bool base) {this->base = base;}
    bool IsBuilding() {return building;}
    void SetBuilding(bool building) {this->building = building;}
    bool IsServiceLines() {return serviceLines;}
    void SetServiceLines(bool serviceLines) {this->serviceLines = serviceLines;}
    bool IsFinish() {return finish;}
    void SetFinish(bool finish) {this->finish = finish;}

    string YesNo(bool r){return r ? "Recieved" : "No";}

    string ToString()
    {
        string sb;
        string result;

        sb.append("Permission to building: ");
        result.append(YesNo(IsBase()));
        sb.append(result);
        sb.append("\n");
        result.clear();

        sb.append("Approval of the estimate: ");
        result.append(YesNo(IsBuilding()));
        sb.append(result);
        sb.append("\n");
        result.clear();

        sb.append("Permission to serviceLines: ");
        result.append(YesNo(IsServiceLines()));
        sb.append(result);
        sb.append("\n");
        result.clear();

        sb.append("Enter to expluatation: ");
        result.append(YesNo(IsFinish()));
        sb.append(result);
        sb.append("\n");
        result.clear();

        return sb;
    }
};
/*******************************/
class Builder
{
public:
    virtual void Reset() = 0;
    virtual void Prepare() = 0;
    virtual void MainWork() = 0;
    virtual void AddServiceLines() = 0;
    virtual void Finish() = 0;
};

class HouseBuilder : public Builder
{
private:
    House* house;
public:
    void Reset() {this->house = new House();}
    void Prepare()
    {
        cout << "Making base" << endl;
        house->SetBase(true);
    }
    void MainWork()
    {
        cout << "Making building" << endl;
        house->SetBuilding(true);
    }
    void AddServiceLines()
    {
        cout << "Making service lines" << endl;
        house->SetServiceLines(true);
    }
    void Finish()
    {
        cout << "Making finish" << endl;
        house->SetFinish(true);
    }

    House* GetResult() {return house;}
};

class PriceBuilder : public Builder
{
private:
    int total;
public:
    void Reset(){total = 0;}
    void Prepare() {total +=500;}
    void MainWork() {total += 1500;}
    void AddServiceLines() {total += 300;}
    void Finish() {total += 400;}
    int GetResult() {return total;}
};

class DocBuilder : public Builder
{
private:
    Documentation* doc;
public:
    void Reset() {doc = new Documentation();}
    void Prepare()
    {
        cout << "Obtaining a building permit " << endl;
        doc->SetBase(true);
    }
    void MainWork()
    {
        cout << "Preparation of estimates" << endl;
        doc->SetBuilding(true);
    }
    void AddServiceLines()
    {
        cout << "Documents for connecting communications" << endl;
        doc->SetServiceLines(true);
    }
    void Finish()
    {
        cout << "Commissioning certificate" << endl;
        doc->SetFinish(true);
    }
    Documentation* GetResult() {return doc;}
};
/*******************************/
class Director
{
private:
    Builder* builder;
public:
    Director(Builder* b) : builder(b) {}
    void Make(bool withServiceLines = true)
    {
        builder->Reset();
        builder->Prepare();
        builder->MainWork();
        if(withServiceLines)
            builder->AddServiceLines();
        builder->Finish();
    }
};
/*******************************/
int main()
{
    PriceBuilder* priceBuilder = new PriceBuilder();
    HouseBuilder* houseBuilder = new HouseBuilder();
    DocBuilder* docBuilder = new DocBuilder();

    Director* salesman = new Director(priceBuilder);
    Director* manager = new Director(docBuilder);
    Director* foreman = new Director(houseBuilder);

    salesman->Make(true);
    int price = priceBuilder->GetResult();
    cout << "Salesman price: " << price << endl;
    cout << "----------------" << endl;

    foreman->Make(true);
    House* house = houseBuilder->GetResult();
    cout << "foreman result: " << house->ToString();
    cout << "----------------" << endl;

    manager->Make(true);
    Documentation* doc = docBuilder->GetResult();
    cout << "manager result: " << doc->ToString();
    cout << "----------------" << endl;


    cout << "Hello World!" << endl;
    return 0;
}
