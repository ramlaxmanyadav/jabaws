package compbio.runner.sequence;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;

import org.apache.log4j.Logger;

import compbio.data.sequence.ScoreManager;
import compbio.data.sequence.SequenceUtil;
import compbio.engine.client.SkeletalExecutable;
import compbio.metadata.ResultNotAvailableException;

public class AAProperties extends SkeletalExecutable<AAProperties> {
	private static Logger log = Logger.getLogger(AAProperties.class);

	public AAProperties() {
		addParameters(Arrays.asList("-jar", getLibPath(), "-a"));
	}

	@SuppressWarnings("unchecked")
	@Override
	public ScoreManager getResults(String workDirectory)
			throws ResultNotAvailableException {
		ScoreManager sequences = null;
		try {
			BufferedReader reader = new BufferedReader(new FileReader(new File(
					workDirectory, getOutput())));
			sequences = SequenceUtil.parseAAProp(reader);
			reader.close();
		} catch (FileNotFoundException e) {
			log.error(e.getMessage(), e.getCause());
			throw new ResultNotAvailableException(e);
		} catch (IOException e) {
			log.error(e.getMessage(), e.getCause());
			throw new ResultNotAvailableException(e);
		} catch (NullPointerException e) {
			log.error(e.getMessage(), e.getCause());
			throw new ResultNotAvailableException(e);
		}
		return sequences;
	}
	@Override
	public AAProperties setOutput(String outFile) {
		super.setOutput(outFile);
		cbuilder.setParam("-o", outFile);
		return this;
	}

	@Override
	public AAProperties setInput(String inFile) {
		super.setInput(inFile);
		cbuilder.setParam("-i", inFile);
		return this;
	}

	private static String getLibPath() {
		String settings = ph.getProperty("aaproperties.jar.file");
		if (compbio.util.Util.isEmpty(settings)) {
			throw new NullPointerException(
					"Please define aaproperties.jar.file property in Executable.properties file"
							+ "and initialize it with the location of jronn jar file");
		}
		if (new File(settings).isAbsolute()) {
			// the jar can be found so no actions necessary
			// no further actions is necessary
			return settings;
		}
		return compbio.engine.client.Util.convertToAbsolute(settings);
	}

	@SuppressWarnings("unchecked")
	@Override
	public Class<AAProperties> getType() {
		return (Class<AAProperties>) this.getClass();
	}

}
