

vector<LG_Primitive *> LG_Graph_Node::handlePrimitives(LG_Node_Map *map, TiXmlElement *primitivesElement){

	vector<LG_Primitive *> primitives;

	TiXmlElement *potentialPrimitive = primitivesElement->FirstChildElement();

	while (potentialPrimitive) {



		if (str_eq(LG_Torus_XML_Tag_Name, potentialPrimitive->Value())) {
			primitives.push_back(new LG_Torus(map, potentialPrimitive));
		}
		else if (str_eq(LG_Sphere_XML_Tag_Name, potentialPrimitive->Value())) {
			primitives.push_back(new LG_Sphere(map, potentialPrimitive));
		}
		else if (str_eq(LG_Cylinder_XML_Tag_Name, potentialPrimitive->Value())) {
			primitives.push_back(new LG_Cylinder(map, potentialPrimitive));
		}
		else if (str_eq(LG_Triangle_XML_Tag_Name, potentialPrimitive->Value())) {
			primitives.push_back(new LG_Triangle(map, potentialPrimitive));
		}
		else if (str_eq(LG_Rectangle_XML_Tag_Name, potentialPrimitive->Value())) {
			primitives.push_back(new LG_Rectangle(map, potentialPrimitive));
		}
		else if (str_eq(LG_Plane_XML_Tag_Name, potentialPrimitive->Value())){

			primitives.push_back(new LG_Plane(map, potentialPrimitive));
		}
		else if (str_eq(LG_Patch_XML_Tag_Name, potentialPrimitive->Value())){
			primitives.push_back(new LG_Patch(map, potentialPrimitive));
		}
		else if (str_eq(LG_Flag_XML_Tag_Name, potentialPrimitive->Value())){
			primitives.push_back(new LG_Flag(map, potentialPrimitive));
		}
		potentialPrimitive = potentialPrimitive->NextSiblingElement();
	}


	return primitives;
}

