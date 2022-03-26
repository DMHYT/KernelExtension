#ifndef KEX_BREATHABLECOMPONENT_HPP
#define KEX_BREATHABLECOMPONENT_HPP


class BreathableComponent {
    public:
    short getMaxAirSupply() const;
    bool canBreatheWater() const;
    int getInhaleTime() const;
    void setAirSupply(short);
    int getSuffocateTime() const;
    void setMaxAirSupply(short);
    bool generatesBubbles() const;
    bool canBreathSolids() const;
    short getAirSupply() const;
    short getAirRegenPerTick() const;
    bool canBreatheAir() const;
    bool canBreatheLava() const;
};


#endif //KEX_BREATHABLECOMPONENT_HPP