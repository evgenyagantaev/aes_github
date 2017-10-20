enum class BinaryCommand : unsigned char {
    COMM_CURRENT_DATA_REQUEST   = 0x01,
    ANSW_CURRENT_DATA           = 0x81,

    COMM_START_TEST             = 0x02,
    ANSW_TEST_COMPLETE          = 0x82
};

int main()
{
    auto command {BinaryCommand::COMM_START_TEST};
//    BinaryCommand command = BinaryCommand::COMM_START_TEST; // Если не поддерживается автоматический вывод типов или brace-initialization

    switch (command) {
    case BinaryCommand::COMM_CURRENT_DATA_REQUEST:
        // Замер данных и отправка их с меткой BinaryCommand::ANSW_CURRENT_DATA
        break;
    case BinaryCommand::COMM_START_TEST:
        // Проведение теста и отправка BinaryCommand::ANSW_TEST_COMPLETE
        break;
    default:
        break;
    }

    return 0;
}
