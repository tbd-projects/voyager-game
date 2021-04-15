#pragma pack

class ProgressLoader : {
public:
    virtual load(int player_id) = 0;

    virtual save(int player_id) = 0;

    virtual ~ProgressLoader();
};

class BaseProgressLoader : public ProgressLoader {
public:
    BaseProgressLoader(std::string root_path);
};