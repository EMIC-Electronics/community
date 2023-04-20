uint32_t getPPM(uint32_t actualtemp, uint32_t actualhumd)
{
	return _{driver}__getppmtemphumd(MQ_DEFAULTRO, uint32_t actualtemp, uint32_t actualhumd);
}

uint32_t getRO(uint32_t actualtemp, uint32_t actualhumd)
{
	return _{driver}__getrotemphumd(MQ_DEFAULTPPM, uint32_t actualtemp, uint32_t actualhumd);
}