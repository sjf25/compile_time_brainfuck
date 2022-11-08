#include <array>
#include <string>

#define STRINGIFY(...) #__VA_ARGS__
#define MAKE_STRING(...) STRINGIFY(__VA_ARGS__)

auto constexpr TAPE_SIZE = 4096;
auto constexpr STACK_SIZE = 4096;
auto constexpr OUTPUT_SIZE = 4096;

template <std::array<uint8_t, OUTPUT_SIZE>> struct print;

consteval auto eval(const auto & instructions, const auto & input)
{
	std::array<uint8_t, TAPE_SIZE> tape{};
	std::array<uint8_t, STACK_SIZE> stack{};
	std::array<uint8_t, OUTPUT_SIZE> output;
	std::size_t tape_idx = 0, pc = 0, sp = 0, out_idx = 0;
	auto input_it = input.begin();

	while(pc < instructions.size())
	{
		uint8_t symbol = instructions[pc];
		switch(symbol)
		{
			case '+':
				tape[tape_idx]++;
				pc++;
				break;
			case '-':
				tape[tape_idx]--;
				pc++;
				break;
			case '>':
				tape_idx++;
				pc++;
				break;
			case '<':
				tape_idx--;
				pc++;
				break;
			case '.':
				output[out_idx] = tape[tape_idx];
				out_idx++;
				pc++;
				break;
			case ',':
				tape[tape_idx] = *input_it++;
				pc++;
				break;
			case '[':
				if(tape[tape_idx] == 0)
				{
					uint64_t count = 0;
					do {
						if(instructions[pc] == '[')
							count++;
						else if(instructions[pc] == ']')
							count--;
						pc++;
					} while(count > 0);
				}
				else
				{
					stack[sp] = pc;
					sp++;
					pc++;
				}
				break;
			case ']':
				sp--;
				pc = stack[sp];
				break;
		}
	}

	return output;
}

int main()
{
	constexpr std::string_view instructions = MAKE_STRING(BF_PROGRAM);
	constexpr std::string_view input = MAKE_STRING(BF_INPUT);
	constexpr auto output = eval(instructions, input);

	print<output> _{};
}
