#include "UIView.h"
#include <DxLib.h>
#include <ostream>
#include <algorithm>
#include <iostream>

UIView::UIView(Rect frame)
{
	this->originalFrame = frame;
	this->relativeFrame = frame;
	this->subViews = std::vector<UIView*>(0);
}

void UIView::Update()
{
	this->UpdateRelativeParent();
	if (!hidden && (!parent || parent && !parent->hidden)) {
		this->CheckMouseOver();
		this->CheckMouseClick();
		this->Draw();
	}

	std::for_each(begin(subViews), end(subViews), [](UIView* &i) {
		i->Update();
	});
}

void UIView::addSubView(UIView* view)
{
	view->parent = this;
	this->subViews.push_back(view);
}

///////// �C�x���g���� ///////////
/// * �}�E�X�J�[�\������ɂ���Ƃ��̃C�x���g
// �}�E�X�J�[�\������ԍŏ��ɏ�ɏ������
void UIView::setOnMouseOverBeginCallback(void(* beginMouseOverCallback)(UIView*))
{
	this->beginMouseOverCallback = beginMouseOverCallback;
}

// �}�E�X�J�[�\������ɏ���Ă��鎞
void UIView::setOnMouseOverWhileCallback(void(* whileMouseOverCallback)(UIView*))
{
	this->whileMouseOverCallback = whileMouseOverCallback;
}

// �}�E�X�J�[�\�����ォ�痣�ꂽ��
void UIView::setOnMouseOverEndCallback(void(* endMouseOverCallback)(UIView*))
{
	this->endMouseOverCallback = endMouseOverCallback;
}

/// * �}�E�X�ɃN���b�N���ꂽ���̃C�x���g
// �}�E�X�Ɉ�ԍŏ��ɃN���b�N���ꂽ��
void UIView::setOnMouseClickBeginCallback(void(* beginMouseClickCallback)(UIView*, EnumMouseClickKind))
{
	this->beginMouseClickCallback = beginMouseClickCallback;
}

// �}�E�X�ɃN���b�N����Ă��鎞 (�z�[���h)
void UIView::setOnMouseClickWhileCallback(void(*whileMouseClickCallback)(UIView*, EnumMouseClickKind))
{
	this->whileMouseClickCallback = whileMouseClickCallback;
}

// �}�E�X�̃N���b�N���I�������
void UIView::setOnMouseClickEndCallback(void(*endMouseClickCallback)(UIView*, EnumMouseClickKind))
{
	this->endMouseClickCallback = endMouseClickCallback;
}

// �`�揈��
void UIView::Draw() const
{
	// �w�i�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, backgroundAlpha);
	DrawFillBox(
		relativeFrame.minX(), relativeFrame.minY(),
		relativeFrame.maxX(), relativeFrame.maxY(), backgroundColor);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//////////////////////////////////

// �e�Ƃ̏����X�V����
void UIView::UpdateRelativeParent()
{
	if (this->parent)
	{
		// ���W���̍X�V
		relativeFrame.point.x = 
			parent->relativeFrame.minX() + originalFrame.minX();
		relativeFrame.point.y =
			parent->relativeFrame.minY() + originalFrame.minY();
	}
	// �I���W�i���̃T�C�Y���X�V
	relativeFrame.size = originalFrame.size;
}

// �}�E�X���̈�̏�ɂ��邩�`�F�b�N����
void UIView::CheckMouseOver()
{
	// �}�E�X�̍��W�擾
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	// �}�E�X�̍��W���I�u�W�F�N�g�̗̈�ɓ����Ă��邩
	this->isMouseOver =
		mouseX >= this->relativeFrame.minX() && 
		this->relativeFrame.maxX() > mouseX &&
		mouseY >= this->relativeFrame.minY() && 
		this->relativeFrame.maxY() > mouseY;

	if (this->isMouseOver)
	{ // �}�E�X���̈�ɓ����Ă���
		// �O�̃t���[���Ń}�E�X���̈�ɓ����Ă��邩
		if (!isMouseOverBeforeFrame)
		{
			// �O�̃t���[���ŗ̈�ɓ����Ă��Ȃ������� (�ŏ�)
			this->isMouseOverBeforeFrame = true;
			if (this->beginMouseOverCallback && enabled)
			{
				// �C�x���g
				this->beginMouseOverCallback(this);
			}
		}
		else
		{
			// �O�̃t���[���ł��̈�ɓ����Ă����� (�Œ�)
			// while
			if (this->whileMouseOverCallback && enabled)
			{
				this->whileMouseOverCallback(this);
			}
		}
	}
	else
	{
		// �}�E�X���̈�ɓ����Ă��Ȃ�
		if (isMouseOverBeforeFrame && this->endMouseOverCallback && enabled)
		{
			// �O�̃t���[���̓}�E�X���̈�ɓ����Ă����� (�Ō�)
			this->endMouseOverCallback(this);
		}
		this->isMouseOverBeforeFrame = false;
	}
}

// �}�E�X�ɃN���b�N����Ă��邩�`�F�b�N����
void UIView::CheckMouseClick()
{
	// �}�E�X���̈�̏�ɂȂ���
	if(!isMouseOver)
	{
		isMouseClicking = false;
		if(isMouseClickBeforeFrame && endMouseClickCallback && enabled && userInteractionEnabled)
		{
			this->endMouseClickCallback(this, mouseClickingKind);
		}
		isMouseClickBeforeFrame = false;
		mouseClickingKind = EnumMouseClickKind::NONE;
		return;
	}
	// �}�E�X�ɃN���b�N����Ă��邩 ���� �}�E�X����ɂ��邩
	int Mouse = GetMouseInput();
	this->mouseClickingKind =
		Mouse & MOUSE_INPUT_LEFT ? EnumMouseClickKind::LEFT :
		Mouse & MOUSE_INPUT_RIGHT ? EnumMouseClickKind::RIGHT :
		Mouse & MOUSE_INPUT_MIDDLE ? EnumMouseClickKind::CENTER : EnumMouseClickKind::NONE;
	this->isMouseClicking = mouseClickingKind != EnumMouseClickKind::NONE;

	if (this->isMouseClicking)
	{ // �N���b�N����Ă���
	  // �O�̃t���[���ŃN���b�N����Ă��邩
		if (!isMouseClickBeforeFrame)
		{
			// �O�̃t���[���ŃN���b�N����Ă��Ȃ� (�ŏ�)
			isMouseClickBeforeFrame = true;
			if (this->beginMouseClickCallback && enabled && userInteractionEnabled)
			{
				this->beginMouseClickCallback(this, mouseClickingKind);
			}
		}
		else
		{
			// �O�̃t���[���ŃN���b�N����Ă��� (�Œ�)
			if (this->whileMouseClickCallback && enabled && userInteractionEnabled)
			{
				this->whileMouseClickCallback(this, mouseClickingKind);
			}
		}
	}
	else
	{
		// �N���b�N����Ă��Ȃ�
		if (isMouseClickBeforeFrame && this->endMouseClickCallback && enabled && userInteractionEnabled)
		{
			// �O�̃t���[���ŃN���b�N����Ă��� (�Ō�)
			this->endMouseClickCallback(this, mouseClickingKind);
		}
		isMouseClickBeforeFrame = false;
	}
}
