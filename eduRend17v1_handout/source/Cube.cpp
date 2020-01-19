#include "Cube.h"
#include "Geometry.h"



Cube::Cube(ID3D11Device* dxdevice,
	ID3D11DeviceContext* dxdevice_context)
	: Geometry_t(dxdevice, dxdevice_context)
{
     //Populate the vertex array with ? vertices
	vertex_t v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23;

	//Z-Normalen
	v0.Pos = { -0.5, -0.5f, 0.0f }; 
	v0.Normal = { 0, 0, 1 };

	v1.Pos = { 0.5, -0.5f, 0.0f };   
	v1.Normal = { 0, 0, 1 };

	v2.Pos = { 0.5, 0.5f, 0.0f };   
	v2.Normal = { 0, 0, 1 };

	v3.Pos = { -0.5, 0.5f, 0.0f };   
	v3.Normal = { 0, 0, 1 };

	v4.Pos = { -0.5, -0.5f, -1 };  
	v4.Normal = { 0, 0, -1 };

	v5.Pos = { 0.5, -0.5f, -1 };  
	v5.Normal = { 0, 0, -1 };

	v6.Pos = { 0.5, 0.5f, -1 };  
	v6.Normal = { 0, 0, -1 };

	v7.Pos = { -0.5, 0.5f, -1 };  
	v7.Normal = { 0, 0, -1 };


	//Y-Normalen
	v8.Pos = { -0.5, -0.5f, 0.0f };
	v8.Normal = { 0, -1, 0 };

	v9.Pos = { 0.5, -0.5f, 0.0f };
	v9.Normal = { 0, -1, 0 };

	v10.Pos = { 0.5, 0.5f, 0.0f };
	v10.Normal = { 0, 1, 0 };

	v11.Pos = { -0.5, 0.5f, 0.0f };
	v11.Normal = { 0, 1, 0 };

	v12.Pos = { -0.5, -0.5f, -1 };
	v12.Normal = { 0, -1, 0 };

	v13.Pos = { 0.5, -0.5f, -1 };
	v13.Normal = { 0, -1, 0 };

	v14.Pos = { 0.5, 0.5f, -1 };
	v14.Normal = { 0, 1, 0 };

	v15.Pos = { -0.5, 0.5f, -1 };
	v15.Normal = { 0, 1, 0 };

	//X-Normalen
	v16.Pos = { -0.5, -0.5f, 0.0f };
	v16.Normal = { -1, 0, 0 };

	v17.Pos = { 0.5, -0.5f, 0.0f };
	v17.Normal = { 1, 0, 0 };

	v18.Pos = { 0.5, 0.5f, 0.0f };
	v18.Normal = { -1, 0, 0 };

	v19.Pos = { -0.5, 0.5f, 0.0f };
	v19.Normal = { 1, 0, 0 };

	v20.Pos = { -0.5, -0.5f, -1 };
	v20.Normal = { -1, 0, 0 };

	v21.Pos = { 0.5, -0.5f, -1 };
	v21.Normal = { 1, 0, 0 };

	v22.Pos = { 0.5, 0.5f, -1 };
	v22.Normal = { -1, 0, 0 };

	v23.Pos = { -0.5, 0.5f, -1 };
	v23.Normal = { 1, 0, 0 };

	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);
	vertices.push_back(v8);
	vertices.push_back(v9);
	vertices.push_back(v10);
	vertices.push_back(v11);
	vertices.push_back(v12);
	vertices.push_back(v13);
	vertices.push_back(v14);
	vertices.push_back(v15); 
	vertices.push_back(v16);
	vertices.push_back(v17);
	vertices.push_back(v18);
	vertices.push_back(v19);
	vertices.push_back(v20);
	vertices.push_back(v21);
	vertices.push_back(v22);
	vertices.push_back(v23);


	// Populate the index array with triangles
    // Triangle #1
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	// Triangle #2
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	// Triangle #3
	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(4);

	// Triangle #4
	indices.push_back(7);
	indices.push_back(4);
	indices.push_back(3);

	// Triangle #5
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(5);

	// Triangle #6
	indices.push_back(2);
	indices.push_back(5);
	indices.push_back(6);

	// Triangle #7
	indices.push_back(4);
	indices.push_back(7);
	indices.push_back(6);

	// Triangle #8
	indices.push_back(5);
	indices.push_back(4);
	indices.push_back(6);

	// Triangle #9
	indices.push_back(3);
	indices.push_back(6);
	indices.push_back(7);

	// Triangle #10
	indices.push_back(6);
	indices.push_back(3);
	indices.push_back(2);

	// Triangle #11
	indices.push_back(0);
	indices.push_back(4);
	indices.push_back(5);

	// Triangle #12
	indices.push_back(0);
	indices.push_back(5);
	indices.push_back(1);


	// Vertex array descriptor
	D3D11_BUFFER_DESC vbufferDesc = { 0.0f };
	vbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbufferDesc.CPUAccessFlags = 0;
	vbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vbufferDesc.MiscFlags = 0;
	vbufferDesc.ByteWidth = vertices.size() * sizeof(vertex_t);
	// Data resource
	D3D11_SUBRESOURCE_DATA vdata;
	vdata.pSysMem = &vertices[0];
	// Create vertex buffer on device using descriptor & data
	HRESULT vhr = dxdevice->CreateBuffer(&vbufferDesc, &vdata, &vertex_buffer);

	//  Index array descriptor
	D3D11_BUFFER_DESC ibufferDesc = { 0.0f };
	ibufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibufferDesc.CPUAccessFlags = 0;
	ibufferDesc.Usage = D3D11_USAGE_DEFAULT;
	ibufferDesc.MiscFlags = 0;
	ibufferDesc.ByteWidth = indices.size() * sizeof(unsigned);
	// Data resource
	D3D11_SUBRESOURCE_DATA idata;
	idata.pSysMem = &indices[0];
	// Create index buffer on device using descriptor & data
	HRESULT ihr = dxdevice->CreateBuffer(&ibufferDesc, &idata, &index_buffer);

	// Local data is now loaded to device so it can be released
	vertices.clear();
	nbr_indices = indices.size();
	indices.clear();

}

void Cube::render() const
{
	//set topology
	dxdevice_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// bind our vertex buffer
	UINT32 stride = sizeof(vertex_t); //  sizeof(float) * 8;
	UINT32 offset = 0;
	dxdevice_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);

	// bind our index buffer
	dxdevice_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);

	// make the drawcall
	dxdevice_context->DrawIndexed(nbr_indices, 0, 0);
}

Cube::~Cube()
{
}