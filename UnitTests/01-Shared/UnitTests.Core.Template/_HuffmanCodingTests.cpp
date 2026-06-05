#include "CppUnitTest.h"

#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Container/Vector.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Compression/HuffmanCoding/_HuffmanDecoder.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Compression/HuffmanCoding/_HuffmanEncoder.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/System/Primitives.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Text/CharacterTraits.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Text/Convert.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::IO::Compression::HuffmanCoding;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::IO::Compression::HuffmanCoding
{
	TEST_CLASS(HuffmanCodingTests)
	{
		using BinaryHuffmanEncoder = HuffmanEncoder<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>;
		using BinaryHuffmanDecoder = HuffmanDecoder<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>;
		using BinaryHuffmanSymbolCodeLengthPair = HuffmanSymbolCodeLengthPair<Elysium::Core::Template::System::byte>;
		using BinaryHuffmanUtility = HuffmanUtility<Elysium::Core::Template::System::byte>;
	public:
		TEST_METHOD(UseCalculatedHuffmanCodes)
		{
			const Elysium::Core::Template::System::byte* Input = reinterpret_cast<const Elysium::Core::Template::System::byte*>(_LoremIpsum);
			const Elysium::Core::Template::System::size InputLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(_LoremIpsum);

			const Elysium::Core::Template::System::size InputSize = InputLength * 8;
			const Elysium::Core::Template::Text::String<char> PrintableInputSize = Elysium::Core::Template::Text::Convert<char>::ToString(InputSize);

			BinaryHuffmanEncoder Encoder = BinaryHuffmanEncoder();

			{
				BinaryHuffmanEncoder::SymbolCodeMap TreeBasedCodes = Encoder.CreateTreeBased(Input, InputLength);
				PrintCodes(TreeBasedCodes);
				const Elysium::Core::Template::System::size CompressedSize = Encoder.CalculateCompressedSize(Input, InputLength, TreeBasedCodes);
				const double CompressionRatio = static_cast<double>(CompressedSize) / InputSize * 100.0;

				const Elysium::Core::Template::Text::String<char> PrintableCompressionRatio = Elysium::Core::Template::Text::Convert<char>::ToString(CompressionRatio);
				const Elysium::Core::Template::Text::String<char> PrintableCompressedSize = Elysium::Core::Template::Text::Convert<char>::ToString(CompressedSize);

				Logger::WriteMessage("\r\nCompression ratio: ");
				Logger::WriteMessage(&PrintableCompressionRatio[0]);
				Logger::WriteMessage("% (");
				Logger::WriteMessage(&PrintableInputSize[0]);
				Logger::WriteMessage(" -> ");
				Logger::WriteMessage(&PrintableCompressedSize[0]);
				Logger::WriteMessage(" bits)\r\n-------------------\r\n");

				// ...
				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> CompressedData = Encoder.Compress(Input, InputLength, TreeBasedCodes);
				for (Elysium::Core::Template::System::size i = 0; i < CompressedData.GetLength(); ++i)
				{
					const Elysium::Core::Template::System::byte CurrentByte = CompressedData[i];
					const Elysium::Core::Template::Text::String<char> PrintableByte = Elysium::Core::Template::Text::Convert<char>::ToString(CurrentByte, 2);
					const Elysium::Core::Template::Text::String<char> PrintableByteDecimal = Elysium::Core::Template::Text::Convert<char>::ToString(CurrentByte, 10);
					/*
					Logger::WriteMessage(&PrintableByte[0]);
					Logger::WriteMessage(" (");
					Logger::WriteMessage(&PrintableByteDecimal[0]);
					Logger::WriteMessage(")\r\n");
					*/
				}
				//Logger::WriteMessage("-------------------\r\n");
				
				// ...
				BinaryHuffmanDecoder Decoder = BinaryHuffmanDecoder();
				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> DecompressedData =
					Decoder.DecompressMSB(&CompressedData[0], CompressedData.GetLength(), InputLength, TreeBasedCodes);
				const char* DecompressedText = reinterpret_cast<const char*>(&DecompressedData[0]);
				Logger::WriteMessage("Output: ");
				Logger::WriteMessage(DecompressedText);
				Logger::WriteMessage("\r\n-------------------");

				const Elysium::Core::Template::System::size DecompressedTextLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(DecompressedText);
				Assert::AreEqual(InputLength, DecompressedTextLength);

				for (Elysium::Core::Template::System::size i = 0; i < DecompressedTextLength; ++i)
				{
					Assert::AreEqual(_LoremIpsum[i], DecompressedText[i]);
				}
			}

			{
				BinaryHuffmanEncoder::SymbolCodeMap CanonicalCodes = Encoder.CreateCanonical(Input, InputLength);
				PrintCodes(CanonicalCodes);
				const Elysium::Core::Template::System::size CompressedSize = Encoder.CalculateCompressedSize(Input, InputLength, CanonicalCodes);
				const double CompressionRatio = static_cast<double>(CompressedSize) / InputSize * 100.0;

				const Elysium::Core::Template::Text::String<char> PrintableCompressionRatio = Elysium::Core::Template::Text::Convert<char>::ToString(CompressionRatio);
				const Elysium::Core::Template::Text::String<char> PrintableCompressedSize = Elysium::Core::Template::Text::Convert<char>::ToString(CompressedSize);

				Logger::WriteMessage("\r\nCompression ratio: ");
				Logger::WriteMessage(&PrintableCompressionRatio[0]);
				Logger::WriteMessage("% (");
				Logger::WriteMessage(&PrintableInputSize[0]);
				Logger::WriteMessage(" -> ");
				Logger::WriteMessage(&PrintableCompressedSize[0]);
				Logger::WriteMessage(" bits)\r\n-------------------\r\n");

				// ...
				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> CompressedData = Encoder.Compress(Input, InputLength, CanonicalCodes);
				for (Elysium::Core::Template::System::size i = 0; i < CompressedData.GetLength(); ++i)
				{
					const Elysium::Core::Template::System::byte CurrentByte = CompressedData[i];
					const Elysium::Core::Template::Text::String<char> PrintableByte = Elysium::Core::Template::Text::Convert<char>::ToString(CurrentByte, 2);
					const Elysium::Core::Template::Text::String<char> PrintableByteDecimal = Elysium::Core::Template::Text::Convert<char>::ToString(CurrentByte, 10);
					/*
					Logger::WriteMessage(&PrintableByte[0]);
					Logger::WriteMessage(" (");
					Logger::WriteMessage(&PrintableByteDecimal[0]);
					Logger::WriteMessage(")\r\n");
					*/
				}
				//Logger::WriteMessage("-------------------\r\n");
				
				// ...
				BinaryHuffmanDecoder Decoder = BinaryHuffmanDecoder();
				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> DecompressedData =
					Decoder.DecompressMSB(&CompressedData[0], CompressedData.GetLength(), InputLength, CanonicalCodes);
				const char* DecompressedText = reinterpret_cast<const char*>(&DecompressedData[0]);
				Logger::WriteMessage("Output: ");
				Logger::WriteMessage(DecompressedText);
				Logger::WriteMessage("\r\n-------------------");

				const Elysium::Core::Template::System::size DecompressedTextLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(DecompressedText);
				Assert::AreEqual(InputLength, DecompressedTextLength);

				for (Elysium::Core::Template::System::size i = 0; i < DecompressedTextLength; ++i)
				{
					Assert::AreEqual(_LoremIpsum[i], DecompressedText[i]);
				}
			}
		}

		TEST_METHOD(UseFixedHuffmanCodes)
		{
			// "Fixed huffman code" simply means holding predefined symbols and their code-lengths.
			// So nothing really changes except that I can skip the first three steps.
			// Assuming the fixed/predefined symbols and their code-lengths are sorted already, that leaves only the last step:
			// 5.) Generate canonical codes from that ordering
			
			Elysium::Core::Template::Container::Vector<BinaryHuffmanSymbolCodeLengthPair> FixedSymbolCodeLengths =
				Elysium::Core::Template::Container::Vector<BinaryHuffmanSymbolCodeLengthPair>(4);
			FixedSymbolCodeLengths[0]._Symbol = 'A';
			FixedSymbolCodeLengths[0]._CodeLength = 2;
			FixedSymbolCodeLengths[1]._Symbol = 'B';
			FixedSymbolCodeLengths[1]._CodeLength = 3;
			FixedSymbolCodeLengths[2]._Symbol = 'C';
			FixedSymbolCodeLengths[2]._CodeLength = 3;
			FixedSymbolCodeLengths[3]._Symbol = 'D';
			FixedSymbolCodeLengths[3]._CodeLength = 3;
			PrintCodeLengths(FixedSymbolCodeLengths);

			BinaryHuffmanEncoder::SymbolCodeMap SymbolCodes = BinaryHuffmanUtility::CreateFromSymbolCodeLengths(FixedSymbolCodeLengths);
			PrintCodes(SymbolCodes);
			// -----------------------
			
			constexpr const char* Text = "AACCCDDDBBB";
			const Elysium::Core::Template::System::byte* Input = reinterpret_cast<const Elysium::Core::Template::System::byte*>(Text);
			const Elysium::Core::Template::System::size InputLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Text);

			Logger::WriteMessage("-------------------\r\nInput: ");
			Logger::WriteMessage(Text);

			const Elysium::Core::Template::System::size InputSize = InputLength * 8;
			const Elysium::Core::Template::Text::String<char> PrintableInputSize = Elysium::Core::Template::Text::Convert<char>::ToString(InputSize);
			// -----------------------

			BinaryHuffmanEncoder Encoder = BinaryHuffmanEncoder();
			const Elysium::Core::Template::System::size CompressedSize = Encoder.CalculateCompressedSize(Input, InputLength, SymbolCodes);
			const double CompressionRatio = static_cast<double>(CompressedSize) / InputSize * 100.0;

			const Elysium::Core::Template::Text::String<char> PrintableCompressionRatio = Elysium::Core::Template::Text::Convert<char>::ToString(CompressionRatio);
			const Elysium::Core::Template::Text::String<char> PrintableCompressedSize = Elysium::Core::Template::Text::Convert<char>::ToString(CompressedSize);

			Logger::WriteMessage("\r\nCompression ratio: ");
			Logger::WriteMessage(&PrintableCompressionRatio[0]);
			Logger::WriteMessage("% (");
			Logger::WriteMessage(&PrintableInputSize[0]);
			Logger::WriteMessage(" -> ");
			Logger::WriteMessage(&PrintableCompressedSize[0]);
			Logger::WriteMessage(" bits)\r\n-------------------\r\n");

			// ...
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> CompressedData = Encoder.Compress(Input, InputLength, SymbolCodes);
			for (Elysium::Core::Template::System::size i = 0; i < CompressedData.GetLength(); ++i)
			{
				const Elysium::Core::Template::System::byte CurrentByte = CompressedData[i];
				const Elysium::Core::Template::Text::String<char> PrintableByte = Elysium::Core::Template::Text::Convert<char>::ToString(CurrentByte, 2);
				const Elysium::Core::Template::Text::String<char> PrintableByteDecimal = Elysium::Core::Template::Text::Convert<char>::ToString(CurrentByte, 10);

				Logger::WriteMessage(&PrintableByte[0]);
				Logger::WriteMessage(" (");
				Logger::WriteMessage(&PrintableByteDecimal[0]);
				Logger::WriteMessage(")\r\n");
			}
			Logger::WriteMessage("-------------------\r\n");
			
			// ...
			BinaryHuffmanDecoder Decoder = BinaryHuffmanDecoder();

			{
				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> DecompressedData =
					Decoder.DecompressMSB(&CompressedData[0], CompressedData.GetLength(), InputLength, SymbolCodes);
				const char* DecompressedText = reinterpret_cast<const char*>(&DecompressedData[0]);
				Logger::WriteMessage("Output: ");
				Logger::WriteMessage(DecompressedText);
				Logger::WriteMessage("\r\n-------------------");

				const Elysium::Core::Template::System::size DecompressedTextLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(DecompressedText);
				Assert::AreEqual(InputLength, DecompressedTextLength);

				for (Elysium::Core::Template::System::size i = 0; i < DecompressedTextLength; ++i)
				{
					Assert::AreEqual(Text[i], DecompressedText[i]);
				}
				Logger::WriteMessage("-------------------\r\n");
			}

			{
				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> DecompressedData =
					Decoder.DecompressMSB(&CompressedData[0], CompressedData.GetLength(), InputLength, FixedSymbolCodeLengths);
				const char* DecompressedText = reinterpret_cast<const char*>(&DecompressedData[0]);
				Logger::WriteMessage("Output: ");
				Logger::WriteMessage(DecompressedText);
				Logger::WriteMessage("\r\n-------------------");

				const Elysium::Core::Template::System::size DecompressedTextLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(DecompressedText);
				Assert::AreEqual(InputLength, DecompressedTextLength);

				for (Elysium::Core::Template::System::size i = 0; i < DecompressedTextLength; ++i)
				{
					Assert::AreEqual(Text[i], DecompressedText[i]);
				}
			}
		}
	private:
		void PrintCodeLengths(const Elysium::Core::Template::Container::Vector<BinaryHuffmanSymbolCodeLengthPair>& SymbolCodeLengths)
		{
			for (Elysium::Core::Template::System::size i = 0; i < SymbolCodeLengths.GetLength(); ++i)
			{
				const char Symbol = SymbolCodeLengths[i]._Symbol;
				char PrintableSymbol[2] = { Symbol, 0x00 };

				const Elysium::Core::Template::Text::String<char>& CodeLength =
					Elysium::Core::Template::Text::Convert<char>::ToString(SymbolCodeLengths[i]._CodeLength);

				Logger::WriteMessage("CodeLengths: ");
				Logger::WriteMessage(PrintableSymbol);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage(&CodeLength[0]);
				Logger::WriteMessage("\r\n");
			}
			Logger::WriteMessage("-------------------\r\n");
		}

		void PrintCodes(BinaryHuffmanEncoder::SymbolCodeMap& Codes)
		{
			for (Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::Template::System::uint16_t, HuffmanCode>::FIterator Iterator = Codes.GetBegin();
				Iterator != Codes.GetEnd(); ++Iterator)
			{
				const Elysium::Core::Template::Container::LinkedListNode<Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Template::System::uint16_t, HuffmanCode>>* Node = *Iterator;
				const Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::Template::System::uint16_t, HuffmanCode>& Item = Node->GetItem();

				const char Symbol = Item.GetKey();
				char PrintableSymbol[2] = { Symbol, 0x00 };

				const HuffmanCode& Code = Item.GetValue();
				const Elysium::Core::Template::Text::String<char> PrintableCode = Elysium::Core::Template::Text::Convert<char>::ToString(Code._Bits, 2);

				const Elysium::Core::Template::Text::String<char> PrintableCodeLength = Elysium::Core::Template::Text::Convert<char>::ToString(Code._Length);

				Logger::WriteMessage("Code: ");
				Logger::WriteMessage(PrintableSymbol);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage(&PrintableCode[0]);
				Logger::WriteMessage(" (");
				Logger::WriteMessage(&PrintableCodeLength[0]);
				Logger::WriteMessage(")\r\n");
			}
		}
	private:
		inline static constexpr const char* _LoremIpsum = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi.";
	};
}
