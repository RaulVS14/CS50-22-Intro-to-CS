from readability import get_grade_for_text


def grade_1_test():
    result = get_grade_for_text('One fish. Two fish. Red fish. Blue fish')
    assert result == 'Before Grade 1'


def grade_2_test():
    result = get_grade_for_text(
        'Would you like them here or there? I would not like them here or there. I would not like them anywhere.')
    assert result == 'Grade 2'


def grade_3_test():
    result = get_grade_for_text("Congratulations! Today is your day. You're off to Great Places! You're off and away!")
    assert result == 'Grade 3'


def grade_5_test():
    result = get_grade_for_text(
        'Harry Potter was a highly unusual boy in many ways. For one thing, he hated the summer holidays more than any other time of year. For another, he really wanted to do his homework, but was forced to do it in secret, in the dead of the night. And he also happened to be a wizard.')
    assert result == 'Grade 5'


def grade_7_test():
    result = get_grade_for_text(
        "In my younger and more vulnerable years my father gave me some advice that I've been turning over in my mind ever since.")
    assert result == 'Grade 7'


def grade_8_test():
    result = get_grade_for_text(
        'Alice was beginning to get very tired of sitting by her sister on the bank, and of having nothing to do: once or twice she had peeped into the book her sister was reading, but it had no pictures or conversations in it, "and what is the use of a book," thought Alice "without pictures or conversation?"')
    assert result == 'Grade 8'


def grade_8_second_test():
    result = get_grade_for_text(
        "When he was nearly thirteen, my brother Jem got his arm badly broken at the elbow. When it healed, and Jem's fears of never being able to play football were assuaged, he was seldom self-conscious about his injury. His left arm was somewhat shorter than his right; when he stood or walked, the back of his hand was at right angles to his body, his thumb parallel to his thigh.")
    assert result == 'Grade 8'


def grade_9_test():
    result = get_grade_for_text(
        "There are more things in Heaven and Earth, Horatio, than are dreamt of in your philosophy.")
    assert result == 'Grade 9'


def grade_10_second_test():
    result = get_grade_for_text(
        "It was a bright cold day in April, and the clocks were striking thirteen. Winston Smith, his chin nuzzled into his breast in an effort to escape the vile wind, slipped quickly through the glass doors of Victory Mansions, though not quickly enough to prevent a swirl of gritty dust from entering along with him.")
    assert result == 'Grade 10'


def grade_16_second_test():
    result = get_grade_for_text(
        "A large class of computational problems involve the determination of properties of graphs, digraphs, integers, arrays of integers, finite families of finite sets, boolean formulas and elements of other countable domains.")
    assert result == 'Grade 16+'


if __name__ == "__main__":
    grade_1_test()
    grade_2_test()
    grade_3_test()
    grade_5_test()
    grade_7_test()
    grade_8_test()
    grade_8_second_test()
    grade_9_test()
    grade_10_second_test()
    grade_16_second_test()
