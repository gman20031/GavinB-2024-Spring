export module ArraySize;

export
template<typename Type , size_t size>
size_t ArraySize(Type (&a)[size] )
{
	return size;
}




