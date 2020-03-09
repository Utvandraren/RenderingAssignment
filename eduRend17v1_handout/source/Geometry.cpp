
#include "Geometry.h"

 Geometry_t::Geometry_t(ID3D11Device* dxdevice,
	ID3D11DeviceContext* dxdevice_context)
	: dxdevice(dxdevice),
	dxdevice_context(dxdevice_context)
{

	//Create sampler
	D3D11_SAMPLER_DESC sd =
	{
		//D3D11_FILTER_MIN_MAG_MIP_LINEAR
		//D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT
		//D3D11_FILTER_ANISOTROPIC

		//D3D11_TEXTURE_ADDRESS_CLAMP
		//D3D11_TEXTURE_ADDRESS_MIRROR

		D3D11_FILTER_ANISOTROPIC,               //Filter
		D3D11_TEXTURE_ADDRESS_WRAP,             //AdressU
		D3D11_TEXTURE_ADDRESS_WRAP,             //AdressV
		D3D11_TEXTURE_ADDRESS_WRAP,             //AdressW
		0.0f,                                   //MipLOBBias
		4,                                      //MaxAnisotropy
		D3D11_COMPARISON_NEVER,                 //ComparisonFunc
		{1.0f, 1.0f, 1.0f, 1.0f},               //BorderColor
		-FLT_MAX,                               //MinLOD
		FLT_MAX,                                //MaxLOD

	};

	HRESULT hr;
	ASSERT(hr = dxdevice->CreateSamplerState(&sd, &samplerState));
}

 void Geometry_t::MapCubeMapBuffer(
	 ID3D11Buffer* CubeMap_Buffer,
	 ID3D11ShaderResourceView* map_Cube_TexSRV,
	 ID3D11Resource* map_Cube_Tex,
	 bool isCubeMap)
 {
	 D3D11_MAPPED_SUBRESOURCE resource;
	 dxdevice_context->Map(CubeMap_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	 CubeMapBuffer_t* cube_buffer_ = (CubeMapBuffer_t*)resource.pData;
	 dxdevice_context->PSSetShaderResources(3, 1, &map_Cube_TexSRV);
	 cube_buffer_->isCubeMap = isCubeMap;
	 dxdevice_context->Unmap(CubeMap_Buffer, 0);
 }

void Geometry_t::MapMatrixBuffers(
	ID3D11Buffer* matrix_buffer,
	mat4f ModelToWorldMatrix,
	mat4f WorldToViewMatrix,
	mat4f ProjectionMatrix)
{
	// Map the resource buffer, obtain a pointer and then write our matrices to it
	D3D11_MAPPED_SUBRESOURCE resource;
	dxdevice_context->Map(matrix_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	MatrixBuffer_t* matrix_buffer_ = (MatrixBuffer_t*)resource.pData;
	matrix_buffer_->ModelToWorldMatrix = ModelToWorldMatrix;
	matrix_buffer_->WorldToViewMatrix = WorldToViewMatrix;
	matrix_buffer_->ProjectionMatrix = ProjectionMatrix;
	dxdevice_context->Unmap(matrix_buffer, 0);
}

void Geometry_t::MapLightCameraBuffer(
	ID3D11Buffer* light_camera_buffer,
	vec4f lightPosition,
	vec4f cameraPosition
	)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	dxdevice_context->Map(light_camera_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	LightCamBuffer_t* light_buffer_ = (LightCamBuffer_t*)resource.pData;
	light_buffer_->lightPos = lightPosition;
	light_buffer_->camerPos = cameraPosition;
	dxdevice_context->Unmap(light_camera_buffer, 0);

}

void Geometry_t::MapPhongBuffer(
	ID3D11Buffer* phong_buffer,
	vec4f ambientColor, 
	vec4f diffuseColor, 
	vec4f specularColor)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	dxdevice_context->Map(phong_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	PhongBuffer_t* phong_buffer_ = (PhongBuffer_t*)resource.pData;
	phong_buffer_->ambColor = ambientColor;
	phong_buffer_->diffColor = diffuseColor;
	phong_buffer_->specColor = specularColor;
	dxdevice_context->Unmap(phong_buffer, 0);
}



//Compute and assign TANGENT and BINORMAL for three triangle vertices
void Geometry_t::compute_tangentspace(vertex_t& v0, vertex_t& v1, vertex_t& v2)
{
	vec3f tangent;
	vec3f binormal;
    vec3f D = vec3f(v1.Pos - v0.Pos);
	vec3f E = vec3f(v2.Pos - v0.Pos);
	vec2f F = v1.TexCoord - v0.TexCoord;
	vec2f G = v2.TexCoord - v0.TexCoord;

	float Tx;
	float Ty;
	float Tz;

	float Bx;
	float By;
	float Bz;

	float constant = (1 / ((F.x * G.y) - (F.y * G.x)));

	Tx = constant * (G.y * D.x + (-F.y) * E.x);
	Ty = constant * (G.y * D.y + (-F.y) * E.y);
	Tz = constant * (G.y * D.z + (-F.y) * E.z);

	Bx = constant * ((-G.x) * D.x + F.x * E.x);
	By = constant * ((-G.x) * D.y + F.x * E.y);
	Bz = constant * ((-G.x) * D.z + F.x * E.z);

	tangent = vec3f(Tx, Ty, Tz);
	binormal = vec3f(Bx, By, Bz);

	tangent.normalize();
	binormal.normalize();

	v0.Tangent = v1.Tangent = v2.Tangent = tangent;
	v0.Binormal = v1.Binormal = v2.Binormal = binormal;
}


Quad_t::Quad_t(
	ID3D11Device* dxdevice,
	ID3D11DeviceContext* dxdevice_context)
	: Geometry_t(dxdevice, dxdevice_context)
{
	// Populate the vertex array with 4 vertices
	vertex_t v0, v1, v2, v3;
	v0.Pos = { -0.5, -0.5f, 0.0f };
	v0.Normal = { 0, 0, 1 };
	v0.TexCoord = { 0, 0 };
	v1.Pos = { 0.5, -0.5f, 0.0f };
	v1.Normal = { 0, 0, 1 };
	v1.TexCoord = { 0, 1 };
	v2.Pos = { 0.5, 0.5f, 0.0f };
	v2.Normal = { 0, 0, 1 };
	v2.TexCoord = { 1, 1 };
	v3.Pos = { -0.5, 0.5f, 0.0f };
	v3.Normal = { 0, 0, 1 };
	v3.TexCoord = { 1, 0 };
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

	// Populate the index array with two triangles
	// Triangle #1
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	// Triangle #2
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	// Vertex array descriptor
	D3D11_BUFFER_DESC vbufferDesc = { 0.0f };
	vbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbufferDesc.CPUAccessFlags = 0;
	vbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vbufferDesc.MiscFlags = 0;
	vbufferDesc.ByteWidth = vertices.size()*sizeof(vertex_t);
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
	ibufferDesc.ByteWidth = indices.size()*sizeof(unsigned);
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


void Quad_t::render() const
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


OBJModel_t::OBJModel_t(
	const std::string& objfile,
	ID3D11Device* dxdevice,
	ID3D11DeviceContext* dxdevice_context)
	: Geometry_t(dxdevice, dxdevice_context)
{
	// Load the OBJ
	mesh_t* mesh = new mesh_t();
	mesh->load_obj(objfile);

	std::vector<unsigned> indices;
	size_t i_ofs = 0;

	for (auto& dc : mesh->drawcalls)
	{
		// Append the drawcall indices
		for (auto& tri : dc.tris) 
		{
			indices.insert(indices.end(), tri.vi, tri.vi + 3);
			compute_tangentspace(mesh->vertices[tri.vi[0]], mesh->vertices[tri.vi[1]], mesh->vertices[tri.vi[2]]);
		}
		
		// Create a range
		size_t i_size = dc.tris.size() * 3;
		int mtl_index = dc.mtl_index > -1 ? dc.mtl_index : -1;
		index_ranges.push_back({ i_ofs, i_size, 0, mtl_index });

		i_ofs = indices.size();
	}

	// Vertex array descriptor
	D3D11_BUFFER_DESC vbufferDesc = { 0.0f };
	vbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbufferDesc.CPUAccessFlags = 0;
	vbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vbufferDesc.MiscFlags = 0;
	vbufferDesc.ByteWidth = mesh->vertices.size()*sizeof(vertex_t);
	// Data resource
	D3D11_SUBRESOURCE_DATA vdata;
	vdata.pSysMem = &(mesh->vertices)[0];
	// Create vertex buffer on device using descriptor & data
	HRESULT vhr = dxdevice->CreateBuffer(&vbufferDesc, &vdata, &vertex_buffer);

	// Index array descriptor
	D3D11_BUFFER_DESC ibufferDesc = { 0.0f };
	ibufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibufferDesc.CPUAccessFlags = 0;
	ibufferDesc.Usage = D3D11_USAGE_DEFAULT;
	ibufferDesc.MiscFlags = 0;
	ibufferDesc.ByteWidth = indices.size()*sizeof(unsigned);
	// Data resource
	D3D11_SUBRESOURCE_DATA idata;
	idata.pSysMem = &indices[0];
	// Create index buffer on device using descriptor & data
	HRESULT ihr = dxdevice->CreateBuffer(&ibufferDesc, &idata, &index_buffer);

	// Copy materials from mesh
	append_materials(mesh->materials);

	// Go through materials and load textures (if any) to device

	for (auto& mtl : materials)
	{
		HRESULT hr;
		std::wstring wstr; // for conversion from string to wstring

		// map_Kd (diffuse texture)
		//
		if (mtl.map_Kd.size()) {
			// Convert the file path string to wstring
			wstr = std::wstring(mtl.map_Kd.begin(), mtl.map_Kd.end());
			// Load texture to device and obtain pointers to it
			hr = DirectX::CreateWICTextureFromFile(dxdevice, dxdevice_context, wstr.c_str(), &mtl.map_Kd_Tex, &mtl.map_Kd_TexSRV);
			// Say how it went
			printf("loading texture %s - %s\n", mtl.map_Kd.c_str(), SUCCEEDED(hr) ? "OK" : "FAILED");
		}

		// map_Ks (specular texture)
		if (mtl.map_Ks.size()) {
			// Convert the file path string to wstring
			wstr = std::wstring(mtl.map_Ks.begin(), mtl.map_Ks.end());
			// Load texture to device and obtain pointers to it
			hr = DirectX::CreateWICTextureFromFile(dxdevice, dxdevice_context, wstr.c_str(), &mtl.map_Ks_Tex, &mtl.map_Ks_TexSRV);
			// Say how it went
			printf("loading texture %s - %s\n", mtl.map_Ks.c_str(), SUCCEEDED(hr) ? "OK" : "FAILED");
		}

		// map_bump (normal texture)
		if (mtl.map_bump.size()) {
			// Convert the file path string to wstring
			wstr = std::wstring(mtl.map_bump.begin(), mtl.map_bump.end());
			// Load texture to device and obtain pointers to it
			hr = DirectX::CreateWICTextureFromFile(dxdevice, dxdevice_context, wstr.c_str(), &mtl.map_bump_Tex, &mtl.map_bump_TexSRV);
			// Say how it went
			printf("loading texture %s - %s\n", mtl.map_bump.c_str(), SUCCEEDED(hr) ? "OK" : "FAILED");
		}	
	}

	SAFE_DELETE(mesh);
}

OBJModel_t::~OBJModel_t()
{
	for (auto& mtl : materials) 
	{
		SAFE_RELEASE(mtl.map_Kd_Tex);
		SAFE_RELEASE(mtl.map_Kd_TexSRV);
		SAFE_RELEASE(mtl.map_Ks_Tex);
		SAFE_RELEASE(mtl.map_Ks_TexSRV);
		SAFE_RELEASE(mtl.map_d_Tex);
		SAFE_RELEASE(mtl.map_d_TexSRV);
		SAFE_RELEASE(mtl.map_bump_Tex);
		SAFE_RELEASE(mtl.map_bump_TexSRV);

	}

	SAFE_RELEASE(samplerState);
}

void OBJModel_t::render() const
{
	// Set topology
	dxdevice_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// Bind vertex buffer
	UINT32 stride = sizeof(vertex_t);
	UINT32 offset = 0;
	dxdevice_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);

	// Bind index buffer
	dxdevice_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);

	// Iterate drawcalls
	for (auto& irange : index_ranges)
	{
		// Fetch material
		const material_t& mtl = materials[irange.mtl_index];

		// Bind textures
		dxdevice_context->PSSetShaderResources(0, 1, &mtl.map_Kd_TexSRV);
		dxdevice_context->PSSetShaderResources(1, 1, &mtl.map_bump_TexSRV);
		dxdevice_context->PSSetShaderResources(2, 1, &mtl.map_Ks_TexSRV);
		// ...other textures here (see material_t)

		//bind sampler
		dxdevice_context->PSSetSamplers(0, 1, &samplerState);

		// Make the drawcall
		dxdevice_context->DrawIndexed(irange.size, irange.start, 0);
	}


}


