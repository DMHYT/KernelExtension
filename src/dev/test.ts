// no tests in use

const TestIntEnum = new Commands.EnumBuilder.Int("testInt")
	.put("A", 1)
	.put("B", 2)
	.put("C", 3)
	.register();

const TestStrEnum = new Commands.EnumBuilder.String("testStr")
	.put("A")
	.put("B")
	.put("C")
	.register();


new Commands.Builder("/test")
	.addOverload({
		test: {
			type: Commands.ArgumentType.BOOL,
		},
		testIntEnum: {
			type: TestIntEnum,
			default: 1
		},
		testStrEnum: {
			type: TestStrEnum,
		}
	}, (args) => {
		args.test // number
		args.testIntEnum // number
		args.testStrEnum // string
	})
	.register();
