

class CoEnemy
{
public:

	std::shared_ptr<Enemy> m_enemy;

	boco::coroutine<Enemy*>::push_type co;
	//ID@EnemyDB


	//�R���X�g���N�^
	CoEnemy(int id, const std::shared_ptr<Enemy>& bp) :m_id(id), co(move), m_enemy(bp)
	{
	}


	/*
	//�R�s�[�R���X�g���N�^���B����copy�𖾎��I�Ɏg�킹��ꍇ
	CoEnemy(const CoEnemy& rhs) = delete;
	CoEnemy& operator =(const CoEnemy & rhs) = delete;
	void copy(const CoEnemy& rhs)
	{
	m_id = rhs.m_id;

	m_enemy = m_enemy->clone();

	co = boco::coroutine<Enemy*>::push_type(move);

	LOG_DEBUG(L"CopyFunc");
	}*/




	//���[�U�[��`�R�s�[�R���X�g���N�^
	CoEnemy(const CoEnemy& rhs) :m_id(rhs.m_id), co(move), m_enemy(rhs.m_enemy->clone())
	{
		LOG_DEBUG(L"CopyCtor");
	}


	///���[�U�[��`�R�s�[������Z�q
	CoEnemy& operator =(const CoEnemy & rhs) _NOEXCEPT
	{
		m_id = rhs.m_id;

		m_enemy = m_enemy->clone();

		co = boco::coroutine<Enemy*>::push_type(move);

		//LOG_DEBUG(L"Copy=");
	}



		///���[�U�[��`���[�u������Z�q
		CoEnemy& operator =(CoEnemy && rhs) _NOEXCEPT
	{
		if (&rhs != this)
		{
			m_id = rhs.m_id;
			//m_enemy = std::move(rhs.m_enemy);
			m_enemy = rhs.m_enemy;
			rhs.m_enemy.reset();
			co = std::move(rhs.co);
			//LOG_DEBUG(L"shared_ptr:", m_enemy.use_count());
		}

		//LOG_DEBUG(L"Move=");

		return *this;
	}

		///���[�U�[��`���[�u�R���X�g���N�^
		///���[�u������Z�q��p����悤�ɂȂ����̂ŁA���[�u�R���X�g���N�^�Ăяo�����ɂ�Move= MoveCtor�ƕ\�L�����
		CoEnemy(CoEnemy&& rhs) _NOEXCEPT
	{
		*this = std::move(rhs);

		//LOG_DEBUG(L"MoveCtor");
	}

	~CoEnemy() = default;

	static void move(boco::coroutine<Enemy*>::pull_type& yield)
	{
		Enemy* B = yield.get();

		B->moveImpl(yield);
	}

	void draw()const
	{
		m_enemy->draw();
	}

	void update()
	{
		m_enemy->update();

		co(m_enemy.get());
	}
};
