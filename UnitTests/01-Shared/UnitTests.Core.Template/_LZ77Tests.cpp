#include "CppUnitTest.h"

#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Compression/LempelZiv/_LZ77Encoder.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Compression/LempelZiv/_LZ77Decoder.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/System/Primitives.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Text/CharacterTraits.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Text/Convert.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::IO::Compression::LempelZiv;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::IO::Compression::LempelZiv
{
	TEST_CLASS(LZ77Tests)
	{
	private:
		using LZ77ByteEncoder = LZ77Encoder<Elysium::Core::Template::System::byte>;
		using LZ77ByteDecoder = LZ77Decoder<Elysium::Core::Template::System::byte>;
	public:
		TEST_METHOD(DecodeFuzzedData)
		{
			NonUTDecodeFuzzedData(false);
			NonUTDecodeFuzzedData(true);
		}

		TEST_METHOD(SimpleEncodeAndDecode)
		{
			const Elysium::Core::Template::System::byte* Input = reinterpret_cast<const Elysium::Core::Template::System::byte*>(_LoremIpsum);
			const Elysium::Core::Template::System::size InputLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(_LoremIpsum);

			LZ77ByteEncoder Encoder;
			Elysium::Core::Template::Container::Vector<LZ77ByteEncoder::Token> Tokens = Encoder.Write(Input, InputLength);

			for (Elysium::Core::Template::System::size i = 0; i < Tokens.GetLength(); ++i)
			{
				const LZ77ByteEncoder::Token& Token = Tokens[i];
				
				if (0 == Token._Length)
				{
					const char CharLiteral = Token._Literal;
					const char PrintableLiteral[2] = {CharLiteral, '\0'};

					Logger::WriteMessage("Literal: ");
					Logger::WriteMessage(&PrintableLiteral[0]);
					Logger::WriteMessage("\r\n");
				}
				else
				{
					const Elysium::Core::Template::Text::String<char> PrintableLength = Elysium::Core::Template::Text::Convert<char>::ToString(Token._Length);
					const Elysium::Core::Template::Text::String<char> PrintableDistance = Elysium::Core::Template::Text::Convert<char>::ToString(Token._Distance);
					Logger::WriteMessage("Length/Distance: ");
					Logger::WriteMessage(&PrintableLength[0]);
					Logger::WriteMessage("/");
					Logger::WriteMessage(&PrintableDistance[0]);
					Logger::WriteMessage("\r\n");
				}
			}

			LZ77ByteDecoder Decoder;
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Result = Decoder.Read(Tokens);
			Result.PushBack(0x00);

			const char* PrintableResult = reinterpret_cast<char*>(&Result[0]);
			const Elysium::Core::Template::System::size ResultLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(PrintableResult);

			Logger::WriteMessage(_LoremIpsum);
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage(PrintableResult);

			Assert::AreEqual(InputLength, ResultLength);
			Assert::AreEqual(_LoremIpsum, PrintableResult);

			Result.Erase(Result.GetBegin(), Result.GetEnd());
		}
	private:
		inline void NonUTDecodeFuzzedData(const bool CreateIncorrectData)
		{
			LZ77ByteDecoder Decoder;
			for (Elysium::Core::Template::System::size i = 0; i < 1000; ++i)
			{
				Elysium::Core::Template::Container::Vector<LZ77ByteEncoder::Token> Tokens;
				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Expected;

				for (Elysium::Core::Template::System::size i = 0; i < 100; ++i)
				{
					if (Expected.GetLength() > 8388608)
					{	// fuzzing could create a "decompression bomb" so let's have a limit here
						break;
					}

					LZ77ByteEncoder::Token Token{};

					bool MakeLiteral = 0 == Expected.GetLength() || rand() % 2 == 0;
					if (MakeLiteral)
					{
						Token._Length = 0;
						Token._Literal = rand() % 256;

						Expected.PushBack(Token._Literal);
					}
					else
					{
						Elysium::Core::Template::System::size MaxDistance = Expected.GetLength();

						Token._Distance = (rand() % MaxDistance) + 1;
						Token._Length = (rand() % 16) + 3;

						if (CreateIncorrectData)
						{
							if (rand() % 10 == 0)
							{
								Token._Distance = 0;
							}
							if (rand() % 10 == 0)
							{
								Token._Distance = Expected.GetLength() + 5;
							}
						}

						for (Elysium::Core::Template::System::size j = 0; j < Token._Length; ++j)
						{
							Elysium::Core::Template::System::byte Literal = Expected[Expected.GetLength() - Token._Distance];
							Expected.PushBack(Literal);
						}
					}

					Tokens.PushBack(Token);
				}

				if (CreateIncorrectData)
				{
					try 
					{
						Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Result = Decoder.Read(Tokens);
						Assert::Fail();
					}
					catch(...)
					{ }
				}
				else
				{
					Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Result = Decoder.Read(Tokens);

					Assert::AreEqual(Expected.GetLength(), Result.GetLength());
					for (Elysium::Core::Template::System::size x = 0; x < Expected.GetLength(); ++x)
					{
						Assert::AreEqual(Expected[x], Result[x]);
					}
				}

			}
		}
	private:
		inline static constexpr const char* _LoremIpsum = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi.";
	};
}
