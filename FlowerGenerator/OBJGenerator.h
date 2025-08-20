#pragma once
#include <ostream>
#include <string>
#include <vector>
#include "Math.h"
struct OBJModel
{
    std::vector<Math::Vector3> Vertices;
    std::vector<int> Indices;
    //Copies and merge model ptr into master model on which this function is called. 
    void AddModelData(OBJModel* model)
    {
        size_t offset = Vertices.size();
        Vertices.insert(Vertices.end(), model->Vertices.begin(), model->Vertices.end());

        for(size_t i = 0; i < model->Indices.size(); ++i)
        {
            Indices.push_back(model->Indices[i] + offset);
        }
    }
    //Parses model data to .obj file format as string.
    std::string ToString()
    {
        std::string result = "";
        for (int i = 0; i < Vertices.size(); i++)
        {
            result.append("v ");
            result.append(std::to_string(Vertices[i].x));
            result.append(" ");
            result.append(std::to_string(Vertices[i].y));
            result.append(" ");
            result.append(std::to_string(Vertices[i].z));
            result.append("\n");
            
        }
        for (int i = 0; i < Indices.size(); i+=3)
        {
            result.append("f ");
            result.append(std::to_string(Indices[i]));
            result.append(" ");
            result.append(std::to_string(Indices[i + 1]));
            result.append(" ");
            result.append(std::to_string(Indices[i + 2]));
            result.append("\n");
        }
        std::printf("%s\n", result.c_str());
        return result;
    }

    void Rotate(const Math::Vector3& Axis, float Angle)
    {
        for (Math::Vector3& v : Vertices)
        {
            Math::Rotate(v, Axis, Angle);
        }
    }
    
    void AddLocation(const Math::Vector3& Location)
    {
        for (Math::Vector3& v : Vertices)
        {
            Math::AddOffset(v, Location);
        }
    }
    void Scale(const Math::Vector3& Scale)
    {
        for (Math::Vector3& v : Vertices)
        {
            Math::Scale(v, Scale);
        }
    }
};
namespace Parts
{
    //Generates Petal model
    inline OBJModel GeneratePetal(float* petalWidth=nullptr)
    {
        OBJModel result;

    //Vertexes

        //Bottom
        result.Vertices.emplace_back(Math::Vector3(0, 0, -1));
        result.Vertices.emplace_back(Math::Vector3(0, 0, 1));

        //Measure width of the petal near the core.
        if (petalWidth != nullptr)
        {
            *petalWidth = Math::Vector3::Distance(result.Vertices[result.Vertices.size() - 1],
                                                  result.Vertices[result.Vertices.size() - 2]);
        }

        //Middle
        result.Vertices.emplace_back(Math::Vector3(1, -0.25f, -1));
        result.Vertices.emplace_back(Math::Vector3(1, -0.25f, 1));

        //Upper
        result.Vertices.emplace_back(Math::Vector3(1.5f, -0.5f, -0.5f));
        result.Vertices.emplace_back(Math::Vector3(1.5f, -0.5f, 0.5f));

        //Top
        result.Vertices.emplace_back(Math::Vector3(2, -0.60f,0));

        result.Indices.emplace_back(3);
        result.Indices.emplace_back(1);
        result.Indices.emplace_back(2);

        result.Indices.emplace_back(3);
        result.Indices.emplace_back(2);
        result.Indices.emplace_back(4);

        result.Indices.emplace_back(3);
        result.Indices.emplace_back(4);
        result.Indices.emplace_back(5);

        result.Indices.emplace_back(5);
        result.Indices.emplace_back(6);
        result.Indices.emplace_back(4);

        result.Indices.emplace_back(5);
        result.Indices.emplace_back(6);
        result.Indices.emplace_back(7);

        return result;
    }
    //Generates Core part model.
    inline OBJModel GenerateCorePart(float sizeX=1.7f)
    {
        OBJModel result;
        //center
        result.Vertices.emplace_back(Math::Vector3(0, 0.2f, 0));
        //side
        result.Vertices.emplace_back(Math::Vector3(sizeX,0,1.0f));
        result.Vertices.emplace_back(Math::Vector3(sizeX,0,-1.0f));

        result.Indices.emplace_back(1);
        result.Indices.emplace_back(2);
        result.Indices.emplace_back(3);

        return result;
    }
}

