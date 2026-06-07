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
		inline static constexpr const char* _LoremIpsum = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi.";
	};
}
