Mark& Mark::add(const Mark& RO)
{
    _value += int(double(_outOf)/double(RO.outof)*RO._value);
    return this;
}

Mark& Mark::operator+=(const Mark& RO
{
    _value += int(double(_outOf)/double(RO.outof)*RO._value);
    return this;
}

Mark sum(const Mark& LO, const Mark& RO)
{
    Mark S(LO);
    S+= RO;
    return S
}
