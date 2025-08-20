#include <fstream>
#include <iostream>

#include "OBJGenerator.h"

void SaveToFile(const char* fileName, OBJModel* objModel)
{
      std::ofstream outfile(fileName);
    if (outfile.is_open())
    {
        outfile << objModel->ToString()<<'\n';
        outfile.close();
    }
}
void GenerateData(int numberOfPetals,OBJModel* petal, OBJModel* corePiece,float* angleOffset)
{
    *angleOffset = 360/numberOfPetals;

    float petalWidth=0.0f;
    //Generate petal 
    *petal = Parts::GeneratePetal(&petalWidth);

    float apotema = Math::CalculateApotema(petalWidth,numberOfPetals);
    //generate core
    *corePiece = Parts::GenerateCorePart(apotema);

    petal->AddLocation(Math::Vector3(apotema,0,0));

    //I rotated petal around X axis.
    //In that way petal shape look better in my opinion.
    petal->Rotate(Math::Vector3(1,0,0), 180);
}
void GenerateSingleFlower(int numberOfPetals)
{
    OBJModel finalModel;
    
    OBJModel Petal ;
    OBJModel CorePiece;
    float angleOffset = 0.0f;
    
    GenerateData(numberOfPetals,&Petal,&CorePiece,&angleOffset);
    
    for (int i = 0; i < numberOfPetals; i++)
    {
        Petal.Rotate(Math::Vector3(0,1,0), angleOffset);
        finalModel.AddModelData(&Petal);
        CorePiece.Rotate(Math::Vector3(0,1,0), angleOffset);
        finalModel.AddModelData(&CorePiece);
    }
    
    SaveToFile("SingleFlowerModel.obj" , &finalModel);
}
void GenerateDoubleFlower(int numberOfPetals)
{
    OBJModel finalModel;
    
    OBJModel Petal ;
    OBJModel CorePiece;
    float angleOffset = 0.0f;
    
    GenerateData(numberOfPetals,&Petal,&CorePiece,&angleOffset);
    
    for (int i = 0; i < numberOfPetals; i++)
    {
        Petal.Rotate(Math::Vector3(0,1,0), angleOffset);
        finalModel.AddModelData(&Petal);
        CorePiece.Rotate(Math::Vector3(0,1,0), angleOffset);
        finalModel.AddModelData(&CorePiece);
    }

    //Copy whole flower model, scale it and rotate by half of the angleOffset.
    //Then add to final Model

    OBJModel modelCopy  = finalModel;
    modelCopy.Rotate(Math::Vector3(0,1,0), angleOffset/2);
    modelCopy.AddLocation(Math::Vector3(0,-0.1f,0));
    modelCopy.Scale(Math::Vector3(1.2f,1.2f,1.2f));
    finalModel.AddModelData(&modelCopy);
   
    SaveToFile("DoubleFlowerModel.obj" , &finalModel);
}

int main(int argc, char* argv[])
{
    GenerateSingleFlower(6);
    GenerateDoubleFlower(6);
    system("pause");
    return 0;
}
