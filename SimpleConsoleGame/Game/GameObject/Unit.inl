

inline void Unit::SetSpeed(float speed) noexcept
{
    m_Speed = speed;
}

inline void Unit::AddMovePower(const SCE::Vec2& addPower) noexcept
{
    m_MovePower += addPower;
}
