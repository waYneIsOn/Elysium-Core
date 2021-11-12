#include "SymmetricAlgorithm.hpp"

Elysium::Core::Security::Cryptography::SymmetricAlgorithm::SymmetricAlgorithm(const Elysium::Core::uint32_t BlockSize, const Elysium::Core::uint32_t KeySize, const Elysium::Core::uint32_t FeedbackSize, const CipherMode CipherMode, const PaddingMode PaddingMode)
	: _BlockSize(BlockSize), _KeySize(KeySize), _FeedbackSize(FeedbackSize),
	_CipherMode(CipherMode), _PadingMode(PaddingMode)
{ }

Elysium::Core::Security::Cryptography::SymmetricAlgorithm::~SymmetricAlgorithm()
{ }

const Elysium::Core::uint32_t Elysium::Core::Security::Cryptography::SymmetricAlgorithm::GetBlockSize() const
{
	return _BlockSize;
}

const Elysium::Core::uint32_t Elysium::Core::Security::Cryptography::SymmetricAlgorithm::GetKeySize() const
{
	return _KeySize;
}

const Elysium::Core::uint32_t Elysium::Core::Security::Cryptography::SymmetricAlgorithm::GetFeedbackSize() const
{
	return _FeedbackSize;
}
