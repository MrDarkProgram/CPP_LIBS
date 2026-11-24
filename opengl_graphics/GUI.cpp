#include "main.h"

void GUIElement::genVerts()
{
	unsigned texW = texturePtr->GetTextureWidth();
	unsigned texH = texturePtr->GetTextureHeight();
	objPtr->vert = {
		{{0, 0, 0},  {}, {}, {posInTex.x / texW, posInTex.y / texH},                                 192},
		{{0, -1, 0}, {}, {}, {posInTex.x / texW, (posInTex.y + sizeInTex.y) / texH},                 192},
		{{1, 0, 0},  {}, {}, {(posInTex.x + sizeInTex.x) / texW, posInTex.y / texH},                 192},
		{{1, 0, 0},  {}, {}, {(posInTex.x + sizeInTex.x) / texW, posInTex.y / texH},                 192},
		{{0, -1, 0}, {}, {}, {posInTex.x / texW, (posInTex.y + sizeInTex.y) / texH},                 192},
		{{1, -1, 0}, {}, {}, {(posInTex.x + sizeInTex.x) / texW, (posInTex.y + sizeInTex.y) / texH}, 192},
	};
}

GUIElement::GUIElement(vec2 pos, vec2 scl, Texture* texturePtr, vec2 posInTex, vec2 sizeInTex, bool dyn, bool genVerts_, PosMode posMode)
{
	objPtr = UniversalRender2::addObject({});
	pos.y = -pos.y;
	objPtr->pos = { pos, 0 };
	objPtr->scl = { scl, 0 };
	this->posInTex = posInTex;
	this->sizeInTex = sizeInTex;
	this->texturePtr = texturePtr;
	this->dyn = dyn;
	if(dyn) objPtr->mode = dyn_triangles;
	else objPtr->mode = triangles;
	objPtr->alpha = true;
	objPtr->color = { 1, 1, 1, 1 };
	objPtr->mode = drawMode(objPtr->mode | posMode);
	if(genVerts_) genVerts();
}

void GUIElement::enableElement(bool enable)
{
	objPtr->enable = enable;
	if(!dyn) UniversalRender2::setRewrite();
}

void GUIElement::setTexturePosAndSize(vec2 pos, vec2 size)
{
	posInTex = pos;
	sizeInTex = size;
	genVerts();
	if (!dyn) UniversalRender2::setRewrite();
}

object* GUIElement::getObjectPtr()
{
	return objPtr;
}



void GUIText::genVerts()
{
	objPtr->vert.clear();
	unsigned texW = texturePtr->GetTextureWidth();
	unsigned texH = texturePtr->GetTextureHeight();
	float j{}, k{};
	for (int i = 0; i < text.size(); i++) {
		char c = text[i];
		if (c == '\n') {
			j = 0;
			k -= 18.0 / 16;
		}
		else if (charTable.contains(c)) {
			vec2 charPos = charTable.at(c);
			vertexes verts = {
				{vec3{j, k, 0},         {}, {}, {charPos.x * 12 / texW, charPos.y * 18 / texH},               160},
				{vec3{j, k - 1, 0},     {}, {}, {charPos.x * 12 / texW, (charPos.y * 18 + 16) / texH},        160},
				{vec3{j + 1, k, 0},     {}, {}, {(charPos.x * 12 + 12) / texW, charPos.y * 18 / texH},        160},
				{vec3{j + 1, k, 0},     {}, {}, {(charPos.x * 12 + 12) / texW, charPos.y * 18 / texH},        160},
				{vec3{j, k - 1, 0},     {}, {}, {charPos.x * 12 / texW, (charPos.y * 18 + 16) / texH},        160},
				{vec3{j + 1, k - 1, 0}, {}, {}, {(charPos.x * 12 + 12) / texW, (charPos.y * 18 + 16) / texH}, 160},
			};
			objPtr->vert.insert(objPtr->vert.end(), verts.begin(), verts.end());
			j++;
		}
		
	}
	
}

GUIText::GUIText(vec2 pos, float size, Texture* texturePtr, std::string text, bool dyn, PosMode posMode) : GUIElement(pos, {size * 12 / 16, size}, texturePtr, {}, {}, dyn, false, posMode)
{
	this->text = text;
	genVerts();
}

void GUIText::setText(std::string text)
{
	this->text = text;
	genVerts();
	if (!dyn) UniversalRender2::setRewrite();
}