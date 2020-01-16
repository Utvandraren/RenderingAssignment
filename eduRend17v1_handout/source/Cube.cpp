#include "Cube.h"
#include "Geometry.h"



Cube::Cube(ID3D11Device* dxdevice,
	ID3D11DeviceContext* dxdevice_context)
	: Geometry_t(dxdevice, dxdevice_context)
{
     //Populate the vertex array with 4 vertices
	vertex_t v0, v1, v2, v3, v4, v5, v6, v7;
	v0.Pos = { -0.5, -0.5f, 0.0f }; 
	v1.Pos = { 0.5, -0.5f, 0.0f };   
	v2.Pos = { 0.5, 0.5f, 0.0f };   
	v3.Pos = { -0.5, 0.5f, 0.0f };   
	v4.Pos = { -0.5, -0.5f, -1 };  
	v5.Pos = { 0.5, -0.5f, -1 };  
	v6.Pos = { 0.5, 0.5f, -1 };  
	v7.Pos = { -0.5, 0.5f, -1 };  

	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);


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